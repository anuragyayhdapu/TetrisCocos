#pragma once

#include "Constants.h"
#include "message.pb.h"

class Board;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const Board& board, TetrisEvent _event) {}
	virtual void onNetworkNotify(const tetris::proto::Board&, t_network::Messagetype) {}
};