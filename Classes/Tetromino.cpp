#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}


Tetromino * Tetromino::create(RotationQ rotationQ, BoardPos gridMatrixPoint, int numOfBlocks)
{
	Tetromino* pRet = new(std::nothrow)Tetromino();
	if (pRet && pRet->init(rotationQ, gridMatrixPoint, numOfBlocks))
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


bool Tetromino::init(RotationQ rotationQ, BoardPos gridMatrixPoint, int numOfBlocks)
{
	if (!Node::init())
	{
		return false;
	}

	// initialze at spawn posiiton
	this->gridMatrixPoint = gridMatrixPoint;

	// set template
	this->numUnitBlock = numOfBlocks;
	this->rotationQ = rotationQ;

	// initialize unitBlocks
	setBlocks(&rotationQ.getCurrentRotation());

	return true;
}


void Tetromino::setBlocks(Side side)
{
	for each (auto pos in *side)
	{
		auto x = gridMatrixPoint.x + pos.x;
		auto y = gridMatrixPoint.y + pos.y;

		auto block = UnitBlock::create(x, y);

		unitBlocksVec.push_back(block);
		this->addChild(block);
	}
}


void Tetromino::rotate()
{
	// since each no.of.blocks(side) = no.of.blocks(unitBlocksVec)
	for (int i = 0; i < unitBlocksVec.size(); ++i)
	{
		// new rotation state
		auto side = rotationQ.getCurrentRotation();

		// new positions
		auto x = gridMatrixPoint.x + side.at(i).x;
		auto y = gridMatrixPoint.y + side.at(i).y;

		unitBlocksVec.at(i)->moveAt(BoardPos(x, y));
	}
}


void Tetromino::drawTetromino()
{
	// draw
	for each (auto block in this->unitBlocksVec)
	{
		block->drawBlock();
	}
}


bool Tetromino::moveLeft(BoardPosSet solidBlocks)
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
	--gridMatrixPoint.x;
	return true;
}


bool Tetromino::moveRight(BoardPosSet solidBlocks)
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
	++gridMatrixPoint.x;
	return true;
}


bool Tetromino::moveDown(BoardPosSet solidBlocks)
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
	++gridMatrixPoint.y;
	return true;
}


bool Tetromino::rotateRight(BoardPosSet solidBlocks)
{
	// check if next rotation won't collide with anything
	auto nextRotation = rotationQ.getRightRotation();
	for each (auto pos in nextRotation)
	{
		if (!UnitBlock::checkMoveAt(pos, solidBlocks))
			return false;
	}

	// actually rotate
	rotationQ.rotateRight();
	rotate();

	return true;
}


bool Tetromino::rotateLeft(BoardPosSet solidBlocks)
{
	// check if next rotation won't collide with anything
	auto nextRotation = rotationQ.getLeftRotation();
	for each (auto pos in nextRotation)
	{
		if (!UnitBlock::checkMoveAt(pos, solidBlocks))
			return false;
	}

	// actually rotate
	rotationQ.rotateLeft();
	rotate();

	return false;
}