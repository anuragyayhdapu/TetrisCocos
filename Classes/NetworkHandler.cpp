#include "NetworkHandler.h"

RakNet::RakPeerInterface *NetworkHandler::rakPeerInterface;
NetworkHandler *NetworkHandler::netInstance = nullptr;

NetworkHandler::NetworkHandler()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
}

void NetworkHandler::init()
{
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
	rakPeerInterface = RakNet::RakPeerInterface::GetInstance();
	//rakPeerInterface->Startup(1,);
}

void NetworkHandler::initRecieverServer()
{
	
}

void NetworkHandler::listen(std::string data)
{
	tetris::proto::Board nBoard;

	if (nBoard.ParseFromString(data))
	{
		tetris::proto::Board_MessageType nMessageType = nBoard.messagetype();
		t_network::Messagetype mType = (t_network::Messagetype) nMessageType;
		networkNotify(nBoard, mType);
	}
	else
	{
		CCLOG("uuuhhh");
	}


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
		listen(output);
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