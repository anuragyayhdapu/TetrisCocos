#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
	unitBlocksVec.clear();
	this->removeAllChildrenWithCleanup(true);
	rotationQ = nullptr;
}

Tetromino * Tetromino::createWithBlocks(const Tetromino& old, std::forward_list<BoardPos> blocksPos)
{
	Tetromino* pRet = new(std::nothrow)Tetromino();
	if (pRet && pRet->initWithBlocks(old, blocksPos))
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

bool Tetromino::initWithBlocks(const Tetromino& old, std::forward_list<BoardPos> blocksPos)
{
	if (!Node::init())
	{
		return false;
	}

	this->gridMatrixPoint = old.gridMatrixPoint;
	this->color = old.color;
	this->borderColor = old.borderColor;

	for (auto pos : blocksPos)
	{
		auto block = UnitBlock::create(pos.x, pos.y, this->color, this->borderColor);

		unitBlocksVec.push_back(block);
		this->addChild(block);
	}

	return true;
}


Tetromino * Tetromino::create(RotationQ::Rnode* rotationQ, cocos2d::Color4B _color, cocos2d::Color4B _borderColor, BoardPos gridMatrixPoint, int numOfBlocks)
{
	Tetromino* pRet = new(std::nothrow)Tetromino();
	if (pRet && pRet->init(rotationQ, _color, _borderColor, gridMatrixPoint, numOfBlocks))
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


bool Tetromino::init(RotationQ::Rnode* rotationQ, cocos2d::Color4B _color, cocos2d::Color4B _borderColor, BoardPos gridMatrixPoint, int numOfBlocks)
{
	if (!Node::init())
	{
		return false;
	}

	// initialze at spawn posiiton
	this->gridMatrixPoint = gridMatrixPoint;

	// set template
	this->rotationQ = rotationQ;
	this->color = _color;
	this->borderColor = _borderColor;

	// initialize unitBlocks
	auto sides = this->rotationQ->face;
	for (auto pos : *sides)
	{
		// adjust according to gridmatrix 
		pos += gridMatrixPoint;

		auto block = UnitBlock::create(pos.x, pos.y, this->color, this->borderColor);

		unitBlocksVec.push_back(block);
		this->addChild(block);
	}


	return true;
}


void Tetromino::drawTetromino()
{
	// draw
	for each (auto block in this->unitBlocksVec)
	{
		block->drawBlock();
	}
}


bool Tetromino::moveLeft(const SolidBlocks& solidBlocks)
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


bool Tetromino::moveRight(const SolidBlocks& solidBlocks)
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


bool Tetromino::moveDown(const SolidBlocks& solidBlocks)
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


bool Tetromino::checkMoveDown(const SolidBlocks& solidBlocks) const
{
	// check if any block of tetromino has a problem with moving Down
	for each (auto block in unitBlocksVec)
	{
		if (!block->checkMoveDown(solidBlocks))
			return false;
	}

	return true;
}


void Tetromino::rotate()
{
	// since each no.of.blocks(side) = no.of.blocks(unitBlocksVec)
	for (size_t i = 0; i < unitBlocksVec.size(); ++i)
	{
		// new rotation state
		auto side = rotationQ->face;

		// new positions
		auto newPos = gridMatrixPoint + side->at(i);

		unitBlocksVec.at(i)->moveAt(newPos);
	}
}


bool Tetromino::rotateRight(const SolidBlocks& solidBlocks)
{
	// check if next rotation won't collide with anything
	auto nextRotation = rotationQ->next;
	for (auto pos : *(nextRotation->face))
	{
		if (!UnitBlock::checkMoveAt(gridMatrixPoint + pos, solidBlocks))
			return false;
	}

	// actually rotate
	rotationQ = rotationQ->next;
	rotate();

	return true;
}


bool Tetromino::rotateLeft(const SolidBlocks& solidBlocks)
{
	// check if next rotation won't collide with anything
	auto nextRotation = rotationQ->prev;
	for (auto pos : *(nextRotation->face))
	{
		if (!UnitBlock::checkMoveAt(gridMatrixPoint + pos, solidBlocks))
			return false;
	}

	// actually rotate
	rotationQ = rotationQ->prev;
	rotate();

	return false;
}


void Tetromino::removeBlock(BoardPos pos)
{
	for (auto iter = unitBlocksVec.begin(); iter != unitBlocksVec.end(); ++iter)
	{
		auto block = *iter;
		if (block->getX() == pos.x && block->getY() == pos.y)
		{
			this->removeChild(block);
			unitBlocksVec.erase(iter);
			break;
		}
	}
}