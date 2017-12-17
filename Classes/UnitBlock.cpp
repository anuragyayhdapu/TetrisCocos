#include "UnitBlock.h"

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

void UnitBlock::moveUp()
{
	// calculate new coordinates
	this->_y--;

	// delete node at old place
	this->_drawNode->clear();

	// redraw at new
	this->drawHollow();
}

void UnitBlock::moveDown()
{
	this->_y++;
	this->_drawNode->clear();
	this->drawHollow();
}

void UnitBlock::moveLeft()
{
	this->_x--;
	this->_drawNode->clear();
	this->drawHollow();
}

void UnitBlock::moveRight()
{
	this->_x++;
	this->_drawNode->clear();
	this->drawHollow();
}