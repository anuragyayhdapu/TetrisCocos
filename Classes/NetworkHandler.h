#pragma once

#include "Subject.h"
#include "Observer.h"
#include "Board.h"

class NetworkHandler : public Subject
{
public:
	void initialize();
	void pushDataToNetwork(const Board& board);

private:
	void listenForDataOnNetwork();
};