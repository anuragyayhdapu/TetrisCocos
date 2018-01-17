#pragma once

#include "cocos2d.h"
#include "Tetromino.h"
#include "SolidBlocks.h"
#include "Subject.h"

class Board : public cocos2d::Node, public Subject
{
public:
	Board(std::list<short>::iterator& iter);
	virtual ~Board();
	static Board* createBoard(double u, cocos2d::Vec2 leftTopPoint, std::list<short>::iterator& randListIter);
	virtual bool init(double u, cocos2d::Vec2 leftTopPoint, std::list<short>::iterator& randListIter);

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
	cocos2d::DrawNode *movingTetDrawNode, *solidTetDrawNode, *bucketDrawNode;
	int moveDelaySeconds;
	std::list<short>::iterator& randListIter;	// randList iterator given to generate next tetromino

	void generateBlock();
	void freezeMovableBlock();
	void drawMovingTetromino();
	void drawSolidTetromino();
	void drawBucketInnerGrid(cocos2d::Color4B color = cocos2d::Color4B::BLACK);

	// schedulars
	void moveSchedular(float dt);
	void lineClearShedular(float dt);
	void dropHangingBlocksShedular(float dt);
};