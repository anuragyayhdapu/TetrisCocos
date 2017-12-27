#pragma once

#include "cocos2d.h"
#include "UnitBlock.h"
#include "BoardPos.h"
#include "Constants.h"
#include "Tetromino.h"

class TetrisBoardScene : public cocos2d::Scene
{
public:
	TetrisBoardScene();
	virtual bool init();
	static TetrisBoardScene* createTetrisBoardScene();

	CREATE_FUNC(TetrisBoardScene);

	virtual ~TetrisBoardScene();

private:

	static double _u;				// size of one unit block
	static cocos2d::Vec2 _pl;		// left-top point in grid (point_left)
	static cocos2d::Vec2 _pf;		// first middle point of a unit block in grid (point_first)
	static int moveDelaySeconds;	// speed at which block moves
	UnitBlock* movableBlock;		// only one movable block at a time
	std::map<BoardPos, UnitBlock*, BoardPosComparator> solidBlocks;	// immovable blocks laying down over bed

	void UpdateFunction(float dt);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void generateBlock(int posX = Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH / 2, int posY = 0);
};