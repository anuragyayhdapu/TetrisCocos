#pragma once

#include "cocos2d.h"
#include "Board.h"
#include "GameScene.h"
#include "TetrisFont.h"
#include "TetrisButton.h"
#include "TetrisCricketInitLayer.h"

class TetrisCricketBoardScene : public GameScene
{
public:
	virtual ~TetrisCricketBoardScene() {}
	CREATE_FUNC(TetrisCricketBoardScene);

	void onNotify(const Board& board, TetrisEvent _event);

private:
	virtual bool init();
	void initDrawNodes();
	void initBowlingList();
	Board *board;
	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;
	cocos2d::DrawNode* windowDrawNode, *arrowDrawNode, *txtDrawNode;
	TetrisFont *arrow;
	TetrisButton * b_up, *b_down, *b_gdrop, *b_right, *b_left, *w_up, *w_down;
	float arrow_y;

	std::list<short> bowlingList;	// bowling list in control of other player
	std::list<short>::iterator bowlingListIter;	// list iterators controlled by other player

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	void start();
	void drawWindow();
	void redrawWindow();
	void moveArrowUp();
	void moveArrowDown();
	void redrawArrow();
	void addText();

	TetrisCricketInitLayer* initLayer;
};