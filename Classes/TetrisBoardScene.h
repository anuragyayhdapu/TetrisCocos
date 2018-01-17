#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Observer.h"
#include "Board.h"
#include "Constants.h"
#include <list>

class TetrisBoardScene : public GameScene, public Observer
{
public:
	virtual bool init();
	CREATE_FUNC(TetrisBoardScene);
	
	void onNotify(const Board& board, TetrisEvent _event);

private:

	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;	// first middle point of a unit block in grid (point_first)
	Board* board;
	std::list<short> randList;					// randomly generated list to get next tetromino
	std::list<short>::iterator randListIter;	// randList iterators given to board 
	cocos2d::DrawNode* windowDrawNode;

	void drawWindow();
	void redrawWindow();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};