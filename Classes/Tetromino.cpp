#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}


Tetromino * Tetromino::create(int numOfBlocks,
	Constant::Matrix topGrid, Constant::Matrix rightGrid, Constant::Matrix bottomGrid, Constant::Matrix leftGrid)
{
	Tetromino* pRet = new(std::nothrow)Tetromino();
	if (pRet && pRet->init(numOfBlocks, topGrid, rightGrid, bottomGrid, leftGrid))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}


bool Tetromino::init(int numOfBlocks,
	Constant::Matrix topGrid, Constant::Matrix rightGrid, Constant::Matrix bottomGrid, Constant::Matrix leftGrid)
{
	if (!Node::init())
	{
		return false;
	}

	// initialze at spawn posiiton
	this->rotationState = Constant::SPAWN_ROTATION_STATE;
	this->gridMatrixPoint = Constant::SPAWN_POSITION;

	// set template
	this->numUnitBlock = numOfBlocks;
	this->topGrid = topGrid;
	this->rightGrid = rightGrid;
	this->bottomGrid = bottomGrid;
	this->leftGrid = leftGrid;

	// initialize unitBlocks
	for (int i = 0; i < numUnitBlock; i++)
	{
		auto block = UnitBlock::createUnitBlock();
		unitBlocksVec.push_back(block);
		this->addChild(block);
	}

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


bool Tetromino::rotateRight()
{
	return false;
}


bool Tetromino::rotateLeft()
{
	return false;
}

// only for initial drawing and drawinf after rotation
void Tetromino::drawTetromino()
{
	// get gridMatrixPoint
	Constant::Matrix currentGrid;
	switch (rotationState)
	{
	case Constant::TOP:
		currentGrid =  topGrid;

	case Constant::RIGHT:
		currentGrid = rightGrid;

	case Constant::BOTTOM:
		currentGrid = bottomGrid;

	case Constant::LEFT:
		currentGrid = leftGrid;

	default:
		currentGrid = topGrid;
	}

	int b = 0;
	// for all places with 1 draw unitBlock and add to vector
	for (int i = 0; i < Constant::GRID_MATRIX_SIZE; i++)
	{
		for (int j = 0; i < Constant::GRID_MATRIX_SIZE; j++)
		{
			if (currentGrid[i][j] == 1)
			{
				unitBlocksVec.at(b)->placeAt(i, j);
			}
		}
	}
}