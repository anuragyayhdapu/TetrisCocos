#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}

bool Tetromino::init()
{
	if (!Node::init())
	{
		return false;
	}

	// initialze at spawn posiiton
	this->rotationState = Constant::SPAWN_ROTATION_STATE;
	this->gridMatrixPoint = Constant::SPAWN_POSITION;

	return true;
}


bool Tetromino::moveLeft(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	// check if any block of tetromino has a problem with moving left
	for each (auto block in unitBlocksVec)
	{
		if (!block->checkMoveLeft(solidBlocks))
			return false;
	}

	// actually move all blocks
	for each (auto block in unitBlocksVec)
	{
		block->moveLeft();
	}
	return true;
}

bool Tetromino::moveRight(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	// check if any block of tetromino has a problem with moving right
	for each (auto block in unitBlocksVec)
	{
		if (!block->checkMoveRight(solidBlocks))
			return false;
	}

	// actually move all blocks
	for each (auto block in unitBlocksVec)
	{
		block->moveRight();
	}
	return true;
}

bool Tetromino::moveDown(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	// check if any block of tetromino has a problem with moving Down
	for each (auto block in unitBlocksVec)
	{
		if (!block->checkMoveDown(solidBlocks))
			return false;
	}

	// actually move all blocks
	for each (auto block in unitBlocksVec)
	{
		block->moveDown();
	}
	return true;
}
