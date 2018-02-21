#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Observer.h"
#include "Board.h"

class LocalTetrisBoardScene : public GameScene
{
public:
	virtual bool init();
	CREATE_FUNC(LocalTetrisBoardScene);
	virtual ~LocalTetrisBoardScene() {}

	void onNotify(const Board& board, TetrisEvent _event);

private:
	short PW;	// x position of window in BoardPos
	double _u;			// size of one unit block
	cocos2d::Vec2 p1_pf, p2_pf;	// first middle point of a unit block in grid (point_first)
	Board *p1Board, *p2Board;
	std::list<short> randList;					// randomly generated list to get next tetromino
	std::list<short>::iterator p1RandListIter, p2RandListIter;	// randList iterators given to board
	cocos2d::DrawNode* windowDrawNode;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void randListMoverHelper(std::list<short>::iterator& a, std::list<short>::iterator& b);		// 'a' iterator has moved

	void drawWindow();
	void redrawWindow();
	void start() {}
};