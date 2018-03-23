#include "NetworkHandler.h"

void NetworkHandler::initialize()
{
	// enet network library code goes here
}

// TODO: should run on a seperate thread
void NetworkHandler::listenForDataOnNetwork(t_network::Board networkRawBoardData)
{
	// on a separate thread, continuously listen for incoming packets
	// if any data recieved, unpack it, and notify Scene

	std::list<short>::iterator dummyIter;
	Board b(dummyIter);

	switch (networkRawBoardData.messageType)
	{
	case t_network::GAME_OVER_SIGNAL:
		notify(b, TetrisEvent::GAMEOVER);
		break;

	case t_network::GAME_PAUSE_SIGNAL:
		notify(b, TetrisEvent::GAMEPAUSE);
		break;

	case t_network::GAME_START_SIGNAL:
		notify(b, TetrisEvent::GAMESTART);
		break;

	case t_network::GAME_RESUME_SIGNAL:
		notify(b, TetrisEvent::GAMERESUME);
		break;

	case t_network::ENTIRE_BOARD_STATE:
		b.setScore(networkRawBoardData.score);
		b.setLevel(networkRawBoardData.level);

		// reconstruct moving tet
		t_network::Tetromino nt = networkRawBoardData.movingTet;
		Tetromino *mt = new Tetromino();
		mt->setTetColor(cocos2d::Color4B(nt.color.r, nt.color.g, nt.color.b, nt.color.a));
		mt->setTetBorderColor(cocos2d::Color4B(nt.borderColor.r, nt.borderColor.g, nt.borderColor.b, nt.borderColor.a));
		mt->setGridMatrixPoint(BoardPos(nt.gridMatrixPoint.x, nt.gridMatrixPoint.y));


		break;

	/*case t_network::MOVING_TETROMINO_STATE:
		break;*/

	/*default:
		break;*/
	}


}

// TODO: should be asynchronous function
void NetworkHandler::pushDataToNetwork(const Board& board, t_network::Messagetype messageType)
{
	// recieve data


	// pack 

	// send
}
