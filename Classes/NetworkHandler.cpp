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



	switch (networkRawBoardData.messageType)
	{
	case t_network::GAME_OVER_SIGNAL:
		
		break;

	case t_network::GAME_PAUSE_SIGNAL:
		
		break;

	case t_network::GAME_START_SIGNAL:
		
		break;

	case t_network::GAME_RESUME_SIGNAL:
		
		break;

	case t_network::ENTIRE_BOARD_STATE:
		


		break;

	/*case t_network::MOVING_TETROMINO_STATE:
		break;*/

	/*default:
		break;*/
	}


}

// reconstruct moving tet
void NetworkHandler::fillEntireBoardStateHelper(Board& b, t_network::Board networkRawBoardData)
{
	b.setScore(networkRawBoardData.score);
	b.setLevel(networkRawBoardData.level);

	t_network::Tetromino nt = networkRawBoardData.movingTet;
	Tetromino *mt = new Tetromino();

	// colors
	mt->setTetColor(cocos2d::Color4B(nt.color.r, nt.color.g, nt.color.b, nt.color.a));
	mt->setTetBorderColor(cocos2d::Color4B(nt.borderColor.r, nt.borderColor.g, nt.borderColor.b, nt.borderColor.a));
	// grid matrix point
	mt->setGridMatrixPoint(BoardPos(nt.gridMatrixPoint.x, nt.gridMatrixPoint.y));
	// unitblocks

}

// TODO: should be asynchronous function
void NetworkHandler::pushDataToNetwork(const Board& board, t_network::Messagetype messageType)
{
	// recieve data


	// pack 

	// send
}
