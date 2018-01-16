#pragma once

#include "Constants.h"

class Board;

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const Board& board, TetrisEvent _event) = 0;
};