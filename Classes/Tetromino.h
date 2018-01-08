#pragma once

#include "UnitBlock.h"
#include "Constants.h"
#include "BoardPos.h"
#include "cocos2d.h"
#include "TetrominoTemplates.h"
#include "RotationQ.h"
#include "SolidBlocks.h"

class SolidBlocks;
class UnitBlock;

// base class for all tetrominos
class Tetromino : public cocos2d::Node
{
	//using Side = const std::vector<BoardPos>*;
	//using BoardPosSet = const std::set<BoardPos, BoardPosComparator>&;

public:
	Tetromino();
	virtual ~Tetromino();
	static Tetromino* create(RotationQ::Rnode* rotationQ, cocos2d::Color4B _color, cocos2d::Color4B _borderColor, BoardPos gridMatrixPoint = t_const::SPAWN_POSITION, int numOfBlocks = t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO);
	bool init(RotationQ::Rnode* rotationQ, cocos2d::Color4B _color, cocos2d::Color4B _borderColor, BoardPos gridMatrixPoint, int numOfBlocks);

	bool moveLeft(const SolidBlocks& solidBlocks);
	bool moveRight(const SolidBlocks& solidBlocks);
	bool moveDown(const SolidBlocks& solidBlocks);
	bool checkMoveDown(const SolidBlocks& solidBlocks) const;

	bool rotateRight(const SolidBlocks& solidBlocks);
	bool rotateLeft(const SolidBlocks& solidBlocks);

	void removeBlock(BoardPos pos);
	bool empty() { return unitBlocksVec.empty(); }

	void drawTetromino();

	const std::vector<UnitBlock*>& getUnitBlocksVec() { return unitBlocksVec; }

private:
	std::vector<UnitBlock*> unitBlocksVec;
	BoardPos gridMatrixPoint;	// top left point of gridmatrix
	cocos2d::Color4B color;
	cocos2d::Color4B borderColor;

	RotationQ::Rnode * rotationQ;

	void rotate();
};