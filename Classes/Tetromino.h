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
	using BoardPosMap = const std::map<BoardPos, UnitBlock*, BoardPosComparator>&;

public:
	Tetromino();
	virtual ~Tetromino();
	static Tetromino* create(RotationQ rotationQ, BoardPos gridMatrixPoint = Constant::SPAWN_POSITION, int numOfBlocks = Constant::NUM_OF_UNIT_BLOCKS_IN_TETROMINO);
	bool init(RotationQ rotationQ, BoardPos gridMatrixPoint, int numOfBlocks);

	bool moveLeft(BoardPosMap solidBlocks);
	bool moveRight(BoardPosMap solidBlocks);
	bool moveDown(BoardPosMap solidBlocks);

	bool rotateRight(BoardPosMap solidBlocks);
	bool rotateLeft(BoardPosMap solidBlocks);

	void drawTetromino();

private:
	short numUnitBlock;
	std::vector<UnitBlock*> unitBlocksVec;
	BoardPos gridMatrixPoint;	// top left point of gridmatrix

	RotationQ rotationQ;

	void setBlocks(Side side);

};