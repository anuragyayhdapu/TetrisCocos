#include "NetworkHandler.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include "MessageIdentifiers.h"
#include <thread>


RakNet::RakPeerInterface *NetworkHandler::rakPeer = nullptr;
NetworkHandler *NetworkHandler::netInstance = nullptr;

enum GameMessages
{
	ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM + 1
};

NetworkHandler::NetworkHandler()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
}

void NetworkHandler::init()
{
	auto id0 = std::this_thread::get_id();

	rakPeer = RakNet::RakPeerInterface::GetInstance();
	rakPeer->Startup(t_network::MAX_CONNECTIONS_ALLOWED, &RakNet::SocketDescriptor(t_network::SERVER_PORT, 0), 1);
	rakPeer->SetMaximumIncomingConnections(t_network::MAX_INCOMING_CONNECTIONS_ALLOWED);
	initSenderServer();

	auto id1 = std::this_thread::get_id();

	auto future =  std::async(std::launch::async, std::bind(&NetworkHandler::listen, this));
}

NetworkHandler::~NetworkHandler()
{
	netInstance = nullptr;
}

NetworkHandler * NetworkHandler::getInstance()
{
	if (netInstance == nullptr)
	{
		netInstance = new NetworkHandler;
		netInstance->init();
	}

	return netInstance;
}

void NetworkHandler::initSenderServer()
{
	rakPeer->Connect("127.0.0.1", t_network::SERVER_PORT, 0, 0);
}

void NetworkHandler::initRecieverServer()
{

}

void NetworkHandler::listen()
{

	auto id2 = std::this_thread::get_id();

	RakNet::Packet *packet;

	while (1)
	{
		for (packet = rakPeer->Receive(); packet; rakPeer->DeallocatePacket(packet), packet = rakPeer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				//CCLOG("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				//CCLOG("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				//CCLOG("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				//CCLOG("Our connection request has been accepted.\n");

				// Use a BitStream to write a custom user message
				// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
				/*RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
				bsOut.Write("Hoopla");
				rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);*/
			}
			break;
			case ID_NEW_INCOMING_CONNECTION:
				//CCLOG("A connection is incoming.\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				//CCLOG("The server is full.\n");
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				//CCLOG("We have been disconnected.\n");
				break;
			case ID_CONNECTION_LOST:
				//CCLOG("Connection lost.\n");
				break;
			case ID_GAME_MESSAGE_1:
			{
				std::string data;
				RakNet::BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				bsIn.Read(data);

				tetris::proto::Board nBoard;

				if (nBoard.ParseFromString(data))
				{
					tetris::proto::Board_MessageType nMessageType = nBoard.messagetype();
					t_network::Messagetype mType = (t_network::Messagetype) nMessageType;
					networkNotify(nBoard, mType);
				}
				//CCLOG("%s\n", rs.C_String());
			}
			break;
			default:
				//CCLOG("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}

	/*tetris::proto::Board nBoard;

	if (nBoard.ParseFromString(data))
	{
		tetris::proto::Board_MessageType nMessageType = nBoard.messagetype();
		t_network::Messagetype mType = (t_network::Messagetype) nMessageType;
		networkNotify(nBoard, mType);
	}
	else
	{
		CCLOG("uuuhhh");
	}*/


}


void NetworkHandler::pushDataToNetwork(const Board& board, t_network::Messagetype messageType)
{
	// board
	tetris::proto::Board n_Board;

	// recieve data
	switch (messageType)
	{
	case t_network::Messagetype::GAME_OVER_SIGNAL:

		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_GAME_OVER_SIGNAL);

		break;
	case t_network::Messagetype::GAME_PAUSE_SIGNAL:

		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_GAME_PAUSE_SIGNAL);

		break;
	case t_network::Messagetype::GAME_START_SIGNAL:

		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_GAME_START_SIGNAL);

		break;
	case t_network::Messagetype::GAME_RESUME_SIGNAL:

		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_GAME_RESUME_SIGNAL);

		break;
	case t_network::Messagetype::MOVING_TETROMINO_STATE:
	{
		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_MOVING_TETROMINO_STATE);

		// moving tetromino
		tetris::proto::Tetromino* n_MoveTet = new tetris::proto::Tetromino();
		auto& movingTet = board.getMovingTetromino();
		createNTetrominoHelper(movingTet, n_MoveTet);

		n_Board.set_allocated_movingtet(n_MoveTet);
	}
	break;
	case t_network::Messagetype::ENTIRE_BOARD_STATE:
	{
		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_ENTIRE_BOARD_STATE);

		// solidblocks
		tetris::proto::SolidBlocks* n_SolidBlocks = new tetris::proto::SolidBlocks();
		const auto& solidTetrominos = board.getSolidBlocks().getSolidTetrominos();
		for (const auto solidTetromino : solidTetrominos)
		{
			auto n_SolidTetromino = n_SolidBlocks->add_tetrominos();
			createNTetrominoHelper(*solidTetromino, n_SolidTetromino);
		}

		n_Board.set_level(board.getLevel());
		n_Board.set_score(board.getScore());
		n_Board.set_allocated_solidblocks(n_SolidBlocks);
	}
	break;

	default:
		break;
	}

	// pack 
	std::string output;
	if (n_Board.SerializePartialToString(&output))
	{
		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
		bsOut.Write(output.c_str());
		RakNet::SystemAddress localSystemAddress("127.0.0.1", t_network::SERVER_PORT);
		rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, localSystemAddress, false);
		//listen(output);

	}
	else
	{
		CCLOG("Error");
	}

	// send
}


void NetworkHandler::createNTetrominoHelper(const Tetromino& from, tetris::proto::Tetromino* to)
{
	auto color = from.getNColor();
	auto bColor = from.getBorderColor();
	tetris::proto::Tetromino_Color* nColor = new tetris::proto::Tetromino_Color();
	nColor->set_r(color.r);
	nColor->set_g(color.g);
	nColor->set_b(color.b);
	nColor->set_a(color.a);
	tetris::proto::Tetromino_Color* nbColor = new tetris::proto::Tetromino_Color();
	nbColor->set_r(bColor.r);
	nbColor->set_g(bColor.g);
	nbColor->set_b(bColor.b);
	nbColor->set_a(bColor.a);
	auto gdPoint = from.getGridMatrixPoint();
	tetris::proto::Tetromino_Pos* ngdPos = new tetris::proto::Tetromino_Pos();
	ngdPos->set_x(gdPoint.x);
	ngdPos->set_y(gdPoint.y);
	auto uBlocksVec = from.getUnitBlocksVec();
	for (const auto block : uBlocksVec) {
		auto nUBlocksVec = to->add_unitblocksvec();
		nUBlocksVec->set_x(block->getX());
		nUBlocksVec->set_y(block->getY());
	}
	to->set_allocated_color(nColor);
	to->set_allocated_bordercolor(nbColor);
	to->set_allocated_gridmatrixpoint(ngdPos);
}