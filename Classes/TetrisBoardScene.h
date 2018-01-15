#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Board.h"

class TetrisBoardScene : public GameScene
{
public:
	virtual bool init();
	CREATE_FUNC(TetrisBoardScene);

private:

	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;	// first middle point of a unit block in grid (point_first)
	Board* board;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};