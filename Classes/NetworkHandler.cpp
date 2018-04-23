#include "NetworkHandler.h"

NetworkHandler::NetworkHandler()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
}

void NetworkHandler::initialize()
{
	// enet network library code goes here
}

void NetworkHandler::listen(std::string data)
{
	tetris::proto::Board nBoard;

	if (nBoard.ParseFromString(data))
	{
		CCLOG("hooray");
		tetris::proto::Board_MessageType nMessageType = nBoard.messagetype();
		t_network::Messagetype mType = (t_network::Messagetype) nMessageType;
		networkNotify(nBoard, mType);
	}
	else
	{
		CCLOG("uuuhhh");
	}


}

// TODO: should run on a seperate thread
//void NetworkHandler::listenForDataOnNetwork(t_network::Board networkRawBoardData)
//{
//	// on a separate thread, continuously listen for incoming packets
//	// if any data recieved, unpack it, and notify Scene
//
//
//
//	switch (networkRawBoardData.messageType)
//	{
//	case t_network::GAME_OVER_SIGNAL:
//
//		break;
//
//	case t_network::GAME_PAUSE_SIGNAL:
//
//		break;
//
//	case t_network::GAME_START_SIGNAL:
//
//		break;
//
//	case t_network::GAME_RESUME_SIGNAL:
//
//		break;
//
//	case t_network::ENTIRE_BOARD_STATE:
//
//
//
//		break;
//
//		/*case t_network::MOVING_TETROMINO_STATE:
//			break;*/
//
//			/*default:
//				break;*/
//	}
//
//
//}

// reconstruct moving tet
//void NetworkHandler::fillEntireBoardStateHelper(Board& b, t_network::Board networkRawBoardData)
//{
//	b.setScore(networkRawBoardData.score);
//	b.setLevel(networkRawBoardData.level);
//
//	t_network::Tetromino nt = networkRawBoardData.movingTet;
//	Tetromino *mt = new Tetromino();
//
//	// colors
//	mt->setTetColor(cocos2d::Color4B(nt.color.r, nt.color.g, nt.color.b, nt.color.a));
//	mt->setTetBorderColor(cocos2d::Color4B(nt.borderColor.r, nt.borderColor.g, nt.borderColor.b, nt.borderColor.a));
//	// grid matrix point
//	mt->setGridMatrixPoint(BoardPos(nt.gridMatrixPoint.x, nt.gridMatrixPoint.y));
//	// unitblocks
//
//}

// TODO: should be asynchronous function
void NetworkHandler::pushDataToNetwork(const Board& board, t_network::Messagetype messageType)
{
	/*t_network::Board networkBoard;
	networkBoard.messageType = messageType;
	t_network::Tetromino networkTetromino;*/

	// recieve data
	switch (messageType)
	{
	case t_network::Messagetype::GAME_OVER_SIGNAL:
		break;
	case t_network::Messagetype::GAME_PAUSE_SIGNAL:
		break;
	case t_network::Messagetype::GAME_START_SIGNAL:
		break;
	case t_network::Messagetype::GAME_RESUME_SIGNAL:
		break;
	case t_network::Messagetype::MOVING_TETROMINO_STATE:
		//break;
	//case t_network::Messagetype::ENTIRE_BOARD_STATE:
	{
		// moving tetromino
		tetris::proto::Tetromino* n_MoveTet = new tetris::proto::Tetromino();
		auto& movingTet = board.getMovingTetromino();
		createNTetrominoHelper(movingTet, n_MoveTet);

		// solidblocks
		tetris::proto::SolidBlocks* n_SolidBlocks = new tetris::proto::SolidBlocks();
		const auto& solidTetrominos = board.getSolidBlocks().getSolidTetrominos();
		for (const auto solidTetromino : solidTetrominos) 
		{
			auto n_SolidTetromino = n_SolidBlocks->add_tetrominos();
			createNTetrominoHelper(*solidTetromino, n_SolidTetromino);
		}

		// board
		tetris::proto::Board n_Board;
		n_Board.set_messagetype(tetris::proto::Board_MessageType::Board_MessageType_MOVING_TETROMINO_STATE);
		n_Board.set_level(board.getLevel());
		n_Board.set_score(board.getScore());
		n_Board.set_allocated_movingtet(n_MoveTet);
		n_Board.set_allocated_solidblocks(n_SolidBlocks);

		std::string output;
		if (n_Board.SerializePartialToString(&output))
		{
			CCLOG("success");
			listen(output);
		}
		else
		{
			CCLOG("Error");
		}

		break;
	}

	default:
		break;
	}

	// pack 

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