#pragma once

#include "Constants.h"

class Board;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const Board& board, TetrisEvent _event) = 0;
	virtual void onNetworkNotify(t_network::Board newtworkBoard, t_network::Messagetype) = 0;
};