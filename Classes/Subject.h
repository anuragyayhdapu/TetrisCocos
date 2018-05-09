#pragma once

#include "Observer.h"
#include "Board.h"
#include "Constants.h"
#include <forward_list>
#include "message.pb.h"

class Subject
{
	std::forward_list<Observer*> observers;

protected:
	void notify(const Board& board, TetrisEvent event) {
		for (auto observer : observers)
			observer->onNotify(board, event);
	}

	void networkNotify(const tetris::proto::Board& board, t_network::Messagetype messageType) {
		for (auto observer : observers)
			observer->onNetworkNotify(board, messageType);
	}

public:
	void registerObserver(Observer* observer) {
		observers.push_front(observer);
	}
};