#pragma once

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotifyMoveIterator() = 0;
	virtual void onNotifyGameEnd() = 0;
};