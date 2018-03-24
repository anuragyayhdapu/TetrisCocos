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

	void networkNotify(t_network::Board newtworkBoard, t_network::Messagetype messageType) {
		observer->onNetworkNotify(newtworkBoard, messageType);
	}

public:
	void registerObserver(Observer* observer) {
		this->observer = observer;
	}
};