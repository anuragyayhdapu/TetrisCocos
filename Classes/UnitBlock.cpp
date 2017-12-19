#include "UnitBlock.h"
#include "Constants.h"

USING_NS_CC;

double UnitBlock::_u = 0;
Vec2 UnitBlock::_pf = Vec2();

UnitBlock::UnitBlock()
{
}

UnitBlock::~UnitBlock()
{
}

UnitBlock * UnitBlock::createUnitBlock()
{
	return UnitBlock::create();
}

bool UnitBlock::init()
{
	if (!Node::init())
	{
		return false;
	}

	// initialize to left most block
	_x = _y = 0;

	_drawNode = DrawNode::create();
	this->addChild(_drawNode);

	return true;
}

void UnitBlock::placeAt(int x, int y, Color4F color)
{
	this->_x = x; this->_y = y;
	this->_color = color;
	this->drawHollow();
}

void UnitBlock::drawHollow()
{
	Vec2 midPoint(_pf.x + _x * _u, _pf.y - _y * _u);
	Vec2 origin(midPoint.x - _u / 2, midPoint.y - _u / 2);
	Vec2 destination(midPoint.x + _u / 2, midPoint.y + _u / 2);

	_drawNode->drawRect(origin, destination, this->_color);
}

bool UnitBlock::moveUp(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	BoardPos nextPos(_x, _y - 1); // next position up
	if (solidBlocks.find(nextPos) != solidBlocks.end()
		|| nextPos.y < 0)
	{
		// block is either touching something or has hit the boundraies
		return true;
	}

	// calculate new coordinates
	this->_y--;

	// delete node at old place
	this->_drawNode->clear();

	// redraw at new
	this->drawHollow();

	return false;
}

// only in case when bottom can't be moved, generate new block
bool UnitBlock::moveDown(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	BoardPos nextPos(_x, _y + 1); // next position down
	if (solidBlocks.find(nextPos) != solidBlocks.end()
		|| nextPos.y > Constant::NUM_OF_UNIT_BLOCKS_IN_HEIGHT - 1)
	{
		// block is either touching something or has hit the boundraies
		return false;
	}

	this->_y++;
	this->_drawNode->clear();
	this->drawHollow();
	return true;
}

bool UnitBlock::moveLeft(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	BoardPos nextPos(_x - 1, _y); // next position left
	if(solidBlocks.find(nextPos) != solidBlocks.end() 
		|| nextPos.x < 0)
	{
		return true;
	}

	this->_x--;
	this->_drawNode->clear();
	this->drawHollow();
	return true;
}

bool UnitBlock::moveRight(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks)
{
	BoardPos nextPos(_x + 1, _y); // next position right
	if (solidBlocks.find(nextPos) != solidBlocks.end()
		|| nextPos.x > Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH - 1)
	{
		return true;
	}

	this->_x++;
	this->_drawNode->clear();
	this->drawHollow();
	return true;
}