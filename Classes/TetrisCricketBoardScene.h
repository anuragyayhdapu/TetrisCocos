#pragma once

#include "cocos2d.h"
#include "GameScene.h"

class TetrisCricketBoardScene : public GameScene
{
public:
	TetrisCricketBoardScene() {}
	virtual ~TetrisCricketBoardScene() {}
	CREATE_FUNC(TetrisCricketBoardScene);

	void onNotify(const Board& board, TetrisEvent _event) {}

private:
	virtual bool init();
	void initDrawNodes();
	Board *board;
	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;
	cocos2d::DrawNode* windowDrawNode;

	std::list<short> bowlingList;	// bowling list in control of other player
	std::list<short>::iterator bowlingListIter;	// list iterators controlled by other player

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	void start() {}
};