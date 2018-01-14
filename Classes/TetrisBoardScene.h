#pragma once

#include "cocos2d.h"
#include "Board.h"

class TetrisBoardScene : public cocos2d::Scene
{
public:
	TetrisBoardScene();
	virtual bool init();
	CREATE_FUNC(TetrisBoardScene);

	virtual ~TetrisBoardScene();

private:

	static double _u;				// size of one unit block
	static cocos2d::Vec2 _pl;		// left-top point in grid (point_left)
	static cocos2d::Vec2 _pf;		// first middle point of a unit block in grid (point_first)
	Board* board;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);
};