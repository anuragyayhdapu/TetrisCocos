#pragma once

#include "cocos2d.h"
#include "UnitBlock.h"
#include "BoardPos.h"
#include "Constants.h"
#include "Tetromino.h"
#include "SolidBlocks.h"
#include "DrawData.h"

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
	cocos2d::DrawNode *movingTetDrawNode, *solidTetDrawNode;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void generateBlock();
	void freezeMovableBlock();
	void drawMovingTetromino();
	void drawSolidTetromino();
	static void drawingHelper(const Tetromino* tetromino, cocos2d::DrawNode* drwaNode);

	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);

	// schedulars
	void moveSchedular(float dt);
	void lineClearShedular(float dt);
	void dropHangingBlocksShedular(float dt);
};