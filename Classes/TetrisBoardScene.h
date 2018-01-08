#pragma once

#include "cocos2d.h"
#include "UnitBlock.h"
#include "BoardPos.h"
#include "Constants.h"
#include "Tetromino.h"
#include "SolidBlocks.h"

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
	Tetromino* movableBlock;		// only one movable block at a time
	SolidBlocks* solidBlocks;		// immovable blocks laying down over bed

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void generateBlock(int posX = t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH / 2, int posY = 0);
	void freezeMovableBlock();

	void GoToPauseScene(cocos2d::Ref * pSender);

	void GoToGameOverScene(cocos2d::Ref * pSender);

	void moveSchedular(float dt);
	void lineClearShedular(float dt);
	void dropHangingBlocksShedular(float dt);
};