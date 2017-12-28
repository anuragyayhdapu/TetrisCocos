#pragma once

#include "UnitBlock.h"
#include "Constants.h"
#include "BoardPos.h"
#include "cocos2d.h"
#include "TetrominoTemplates.h"
#include "RotationQ.h"

// base class for all tetrominos
class Tetromino : public cocos2d::Node
{
	using Side = const std::vector<BoardPos>*;
	using BoardPosSet = const std::set<BoardPos, BoardPosComparator>&;

public:
	Tetromino();
	virtual ~Tetromino();
	static Tetromino* create(RotationQ rotationQ, BoardPos gridMatrixPoint = Constant::SPAWN_POSITION, int numOfBlocks = Constant::NUM_OF_UNIT_BLOCKS_IN_TETROMINO);
	bool init(RotationQ rotationQ, BoardPos gridMatrixPoint, int numOfBlocks);

	bool moveLeft(BoardPosSet solidBlocks);
	bool moveRight(BoardPosSet solidBlocks);
	bool moveDown(BoardPosSet solidBlocks);

	bool rotateRight(BoardPosSet solidBlocks);
	bool rotateLeft(BoardPosSet solidBlocks);

	void drawTetromino();

	const std::vector<UnitBlock*>& getUnitBlocksVec() { return unitBlocksVec; }

private:
	short numUnitBlock;
	std::vector<UnitBlock*> unitBlocksVec;
	BoardPos gridMatrixPoint;	// top left point of gridmatrix

	RotationQ rotationQ;

	void setBlocks(Side side);
	void rotate();
};