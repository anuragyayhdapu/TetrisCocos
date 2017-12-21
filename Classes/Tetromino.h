#pragma once

#include "UnitBlock.h"
#include "Constants.h"
#include "BoardPos.h"
#include "cocos2d.h"

// base class for all tetrominos
class Tetromino : public cocos2d::Node
{
public:
	Tetromino();
	virtual ~Tetromino();
	virtual bool init();
	CREATE_FUNC(Tetromino);

	bool moveLeft(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);
	bool moveRight(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);
	bool moveDown(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);

	virtual bool rotateRight();
	virtual bool rotateLeft();

private:
	Constant::RotationState rotationState;
	std::vector<UnitBlock*> unitBlocksVec;
	BoardPos gridMatrixPoint;	// top left point of gridmatrix
	
	bool rightGrid[4][4];
	bool leftGrid[4][4];
	bool topGrid[4][4];
	bool bottomGrid[4][4];
};