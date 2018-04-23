#pragma once

#include "Board.h"
#include "Constants.h"
#include "message.pb.h"


class NetworkHandler : public Subject
{
public:
	NetworkHandler();
	void initialize();
	void pushDataToNetwork(const Board& board, t_network::Messagetype);

private:
	//void listenForDataOnNetwork(t_network::Board);
	void listen(std::string data);

	// helpers
	//void fillEntireBoardStateHelper(Board& b, t_network::Board networkRawBoardData);
	void createNTetrominoHelper(const Tetromino& from, tetris::proto::Tetromino* to);
};