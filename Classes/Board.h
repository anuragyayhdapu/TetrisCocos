#pragma once

#include "cocos2d.h"
#include "Tetromino.h"
#include "SolidBlocks.h"
#include "Subject.h"
#include <forward_list>

class Board : public cocos2d::Node, public Subject
{
public:
	Board(std::list<short>::iterator& iter, short bucketLeft, short bucketRight, short bucketTop, short bucketBottom, BoardPos spawnPoint);
	virtual ~Board();
	static Board* createBoard(double u, cocos2d::Vec2 leftTopPoint, std::list<short>::iterator& randListIter, unsigned int highScore, int level, short bucketLeft, short bucketRight, short bucketTop, short bucketBottom, BoardPos spawnPoint);
	virtual bool init(double u, cocos2d::Vec2 leftTopPoint, std::list<short>::iterator& randListIter, unsigned int highScore, int level);

	void movingBlockDown();
	void movingBlockLeft();
	void movingBlockRight();
	void movingBlockRotate();
	void movingBlockGravityDrop();

	void start();
	void stop();

private:
	short bucketLeft, bucketRight, bucketTop, bucketBottom;
	double _u;			 // size of one unit block
	cocos2d::Vec2 _pf;	 // first middle point of a unit block in grid (point_first)
	Tetromino *movableTetromino;	// only one movable block at a time
	std::forward_list<UnitBlock*> ghostPieces;
	SolidBlocks *solidBlocks;	// immovable blocks laying down over bed
	cocos2d::DrawNode *movingTetDrawNode, *solidTetDrawNode, *bucketDrawNode, *ghostDrawNode;
	float moveDelaySeconds, tempDt;
	std::list<short>::iterator& randListIter;	// randList iterator given to generate next tetromino
	BoardPos spawnPoint;

	unsigned int score, highScore;
	int level;
	short totalLinesClear, lineClearCount;

	void generateBlock();
	void freezeMovableBlock();
	void drawMovingTetromino();
	void drawSolidTetromino();
	void drawBucketInnerGrid(cocos2d::Color4B color = cocos2d::Color4B::BLACK);
	void createGhostPiece();
	void updateGhostPiece();
	bool checkGameOver();
	void updateScore();

	// schedulars
	void moveSchedular(float dt);
	void lineClearShedular(float dt);
	void dropHangingBlocksShedular(float dt);
	bool toUpdate(float dt);

public:
	unsigned int getScore() const { return score; }
	unsigned int getHighScore() const { return highScore; }
	int getLevel() const { return level; }
};