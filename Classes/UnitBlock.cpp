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

UnitBlock * UnitBlock::createunitBlock()
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