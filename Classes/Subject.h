#pragma once

#include "Observer.h"
#include "Board.h"
#include "Constants.h"

class Subject
{
	Observer* observer;

protected:
	void notify(const Board& board, TetrisEvent event) {
		observer->onNotify(board, event);
	}

public:
	void registerObserver(Observer* observer) {
		this->observer = observer;
	}
};