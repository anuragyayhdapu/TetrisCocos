#pragma once

#include "cocos2d.h"
#include "UnitBlock.h"

class TetrisBoardScene : public cocos2d::Scene
{
public:
	TetrisBoardScene();
	virtual bool init();
	static TetrisBoardScene* createTetrisBoardScene();

	CREATE_FUNC(TetrisBoardScene);

	virtual ~TetrisBoardScene();

private:
	
	static double _u;			// size of one unit block
	static cocos2d::Vec2 _pl;	// left-top point in grid (point_left)
	static cocos2d::Vec2 _pf;	// first middle point of a unit block in grid (point_first)
	std::vector<UnitBlock*> movableBlockes;

	static const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 30;
	static const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 25;


	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};