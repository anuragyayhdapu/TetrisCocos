#pragma once

#include "Board.h"
#include "Constants.h"


class NetworkHandler : public Subject
{
public:
	NetworkHandler() {}
	void initialize();
	void pushDataToNetwork(const Board& board, t_network::Messagetype);

private:
	void listenForDataOnNetwork(t_network::Board);
};