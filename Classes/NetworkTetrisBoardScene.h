#pragma once

#include "cocos2d.h"
#include "GameScene.h"

class NetworkTetrisBoardScene : public GameScene
{
public:
	virtual bool init();
	CREATE_FUNC(NetworkTetrisBoardScene);

	void onNotify(const Board& board, TetrisEvent _event) {}

private:
	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;	// first middle point of a unit block in grid

	void handshake();
	void start();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};