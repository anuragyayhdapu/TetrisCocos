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
	double _u;			// size of one unit block
	cocos2d::Vec2 p1_pf, p2_pf;	// first middle point of a unit block in grid (point_first)
	Board *p1Board, *p2Board;
	std::list<short> randList;					// randomly generated list to get next tetromino
	std::list<short>::iterator p1RandListIter, p2RandListIter;	// randList iterators given to board

	cocos2d::DrawNode* windowDrawNode;
	cocos2d::Layer *countDownLayer;
	TetrisFont *p1Score, *p2Score, *p1Level, *p2Level;
	cocos2d::DrawNode* p1DrawNode, p2DrawNode;

	void drawFonts(cocos2d::Size visibleSize);
	void drawWindow();
	void redrawWindow();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void start();
};