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
	static Tetromino* create(int numOfBlocks, Constant::Matrix topGrid, Constant::Matrix rightGrid, Constant::Matrix bottomGrid, Constant::Matrix leftGrid);
	bool init(int numOfBlocks, Constant::Matrix topGrid, Constant::Matrix rightGrid, Constant::Matrix bottomGrid, Constant::Matrix leftGrid);
	/*CREATE_FUNC(Tetromino);*/

	bool moveLeft(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);
	bool moveRight(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);
	bool moveDown(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);

	virtual bool rotateRight();
	virtual bool rotateLeft();

	virtual void drawTetromino();

private:
	Constant::RotationState rotationState;
	short numUnitBlock;
	std::vector<UnitBlock*> unitBlocksVec;
	BoardPos gridMatrixPoint;	// top left point of gridmatrix

	Constant::Matrix topGrid;
	Constant::Matrix rightGrid;
	Constant::Matrix bottomGrid;
	Constant::Matrix leftGrid;

};