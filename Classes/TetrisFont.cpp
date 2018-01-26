#include "TetrisFont.h"
#include "Constants.h"


TetrisFont::TetrisFont()
{
}

TetrisFont::~TetrisFont()
{
}

float TetrisFont::u;

TetrisFont * TetrisFont::create(std::string text, cocos2d::Color3B color, cocos2d::Vec2 position, short size)
{
	TetrisFont* ptr = new(std::nothrow)TetrisFont();
	if (ptr && ptr->init(text, color, position, size))
	{
		ptr->autorelease();
	}
	else
	{
		delete ptr;
		ptr = nullptr;
	}
	return ptr;
}


bool TetrisFont::init(std::string text, cocos2d::Color3B color, cocos2d::Vec2 position, short size)
{
	if (!Node::init())
	{
		return false;
	}

	this->text = text;
	this->size = u * size;
	this->color = color;
	midPt = position;
	calcBoundingBoxPoints();



	return true;
}


void TetrisFont::calcBoundingBoxPoints()
{
	// top left
	leftPt.x = midPt.x - ((text.length() / 2) * size);
	leftPt.y = midPt.y;

	// bottom right
	rightPt.x = midPt.x + ((text.length() / 2) * size);
	rightPt.y = midPt.y - (6 * size);

	// adjust midPoint
	midPt.y -= (3 * size);
}

void TetrisFont::createFontBlocks()
{
}


void TetrisFont::write(cocos2d::DrawNode * drawNode)
{
}