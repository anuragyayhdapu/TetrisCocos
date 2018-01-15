#pragma once

#include "cocos2d.h"
#include "Tetromino.h"
#include "SolidBlocks.h"

class Board : public cocos2d::Node
{
public:
	Board();
	virtual ~Board();
	static Board* createBoard(double u, cocos2d::Vec2 leftTopPoint);
	virtual bool init(double u, cocos2d::Vec2 leftTopPoint);

	void movingBlockDown();
	void movingBlockLeft();
	void movingBlockRight();
	void movingBlockRotate();
	void movingBlockGravityDrop();

private:
	double _u;			 // size of one unit block
	cocos2d::Vec2 _pf;	 // first middle point of a unit block in grid (point_first)
	Tetromino * movableBlock;	// only one movable block at a time
	SolidBlocks* solidBlocks;	// immovable blocks laying down over bed
	cocos2d::DrawNode *movingTetDrawNode, *solidTetDrawNode;
	int moveDelaySeconds;

	void generateBlock();
	void freezeMovableBlock();
	void drawMovingTetromino();
	void drawSolidTetromino();
	static void drawingHelper(const Tetromino* tetromino, cocos2d::DrawNode* drwaNode);

	// schedulars
	void moveSchedular(float dt);
	void lineClearShedular(float dt);
	void dropHangingBlocksShedular(float dt);
};