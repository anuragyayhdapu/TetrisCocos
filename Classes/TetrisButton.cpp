#include "TetrisButton.h"

TetrisButton::TetrisButton(cocos2d::Color4F borderColor)
	:
	borderColor(borderColor)
{
}

TetrisButton::~TetrisButton()
{
}

TetrisButton * TetrisButton::create(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontAlign align, FontColorPattern colorPattern, FontDrawPattern drawPattern, float width)
{
	TetrisButton* ptr = new(std::nothrow)TetrisButton(color);
	if (ptr && ptr->init(text, position, size, colorPattern, drawPattern, align, width))
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

bool TetrisButton::init(std::string text, cocos2d::Vec2 position, float size, FontColorPattern colorPattern, FontDrawPattern drawPattern, FontAlign align, unsigned int width)
{
	if (!Node::init())
	{
		return false;
	}

	fontDrawNode = cocos2d::DrawNode::create();
	this->addChild(fontDrawNode);
	this->font = TetrisFont::create(text, this->borderColor, position, size, colorPattern, drawPattern, align);
	this->addChild(font);
	font->write(fontDrawNode);

	unsigned int diff;
	if (width <= text.size())
		diff = 0;
	else
		diff = width - text.size();


	// give 2 size padding around text
	this->leftPt = font->getLeftPt();
	this->rightPt = font->getRightPt();

	btnDrawNode = cocos2d::DrawNode::create();
	btnDrawNode->drawRect(leftPt, rightPt, cocos2d::Color4F::ORANGE);
	this->addChild(btnDrawNode);

	return true;
}


bool TetrisButton::insideBoundingBox(cocos2d::Vec2 pos)
{
	if (pos.x >= leftPt.x && pos.x <= rightPt.x
		&& pos.y <= leftPt.y && pos.y >= rightPt.y)
	{
		return true;
	}

	return false;
}