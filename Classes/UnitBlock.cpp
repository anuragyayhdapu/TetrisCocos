#include "UnitBlock.h"
#include "Constants.h"

USING_NS_CC;

UnitBlock::UnitBlock()
{
}


UnitBlock * UnitBlock::create(double u, cocos2d::Vec2 pf, short x, short y, cocos2d::Color4B color, cocos2d::Color4B borderColor)
{
	UnitBlock* block = new(std::nothrow)UnitBlock();
	if (block && block->init(u, pf, x, y, color, borderColor))
	{
		block->autorelease();
		return block;
	}
	else
	{
		delete block;
		block = nullptr;
		return nullptr;
	}
}

bool UnitBlock::init(double u, cocos2d::Vec2 pf, short x, short y, cocos2d::Color4B color, cocos2d::Color4B borderColor)
{
	if (!Node::init())
	{
		return false;
	}

	this->_u = u;
	this->_pf = pf;
	this->_x = x;
	this->_y = y;
	drawData.color = cocos2d::Color4F(color);
	drawData.borderColor = cocos2d::Color4F(borderColor);
	calcDrawData();

	return true;
}


void UnitBlock::calcDrawData()
{
	Vec2 midPoint(_pf.x + _x * _u, _pf.y - _y * _u);
	Vec2 origin(midPoint.x - _u / 2, midPoint.y - _u / 2);
	Vec2 destination(midPoint.x + _u / 2, midPoint.y + _u / 2);

	drawData.midPoint = midPoint;
	drawData.origin = origin;
	drawData.destination = destination;
}

void UnitBlock::moveDown()
{
	this->_y++;
	calcDrawData();
}

void UnitBlock::moveLeft()
{
	this->_x--;
	calcDrawData();
}

void UnitBlock::moveRight()
{
	this->_x++;
	calcDrawData();
}

void UnitBlock::moveAt(BoardPos pos)
{
	this->_x = pos.x;
	this->_y = pos.y;
	calcDrawData();
}


bool UnitBlock::checkMoveAt(BoardPos nextPos, const SolidBlocks& solidBlocks)
{
	if (solidBlocks.find(nextPos) == true
		|| nextPos.x < t_const::BUCKET_LEFT || nextPos.x > t_const::BUCKET_RIGHT - 1
		|| nextPos.y < t_const::BUCKET_TOP || nextPos.y > t_const::BUCKET_BOTTOM - 1)
	{
		// block is either touching something or has hit the boundraies
		return false;
	}

	return true;
}

bool UnitBlock::checkMoveDown(const SolidBlocks& solidBlocks)
{
	BoardPos nextPos(_x, _y + 1); // next position down
	if (solidBlocks.find(nextPos) == true
		|| nextPos.y > t_const::BUCKET_BOTTOM - 1)
	{
		// block is either touching something or has hit the boundraies
		return false;
	}
	return true;
}

bool UnitBlock::checkMoveLeft(const SolidBlocks& solidBlocks)
{
	BoardPos nextPos(_x - 1, _y); // next position left
	if (solidBlocks.find(nextPos) == true
		|| nextPos.x < t_const::BUCKET_LEFT)
	{
		// block is either touching something or has hit the boundraies
		return false;
	}
	return true;
}

bool UnitBlock::checkMoveRight(const SolidBlocks& solidBlocks)
{
	BoardPos nextPos(_x + 1, _y); // next position right
	if (solidBlocks.find(nextPos) == true
		|| nextPos.x > t_const::BUCKET_RIGHT - 1)
	{
		// block is either touching something or has hit the boundraies
		return false;
	}
	return true;
}

