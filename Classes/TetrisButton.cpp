#include "TetrisButton.h"

TetrisButton::TetrisButton(cocos2d::Color4F borderColor)
	:
	borderColor(borderColor),
	alreadyClear(true),
	alreadyDrawn(false)
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

	// give padding around text
	unsigned int diff;
	if (width <= text.size())
		diff = 1;
	else
		diff = width - text.size();

	this->leftPt = font->getLeftPt();
	this->rightPt = font->getRightPt();

	float offset = (size * TetrisFont::u * diff);
	leftPt.x -= offset;
	leftPt.y += size * TetrisFont::u;
	rightPt.x += offset;
	rightPt.y -= size * TetrisFont::u;

	btnDrawNode = cocos2d::DrawNode::create();
	this->addChild(btnDrawNode);

	auto mouseListner = cocos2d::EventListenerMouse::create();
	mouseListner->onMouseMove = CC_CALLBACK_1(TetrisButton::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);

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

bool TetrisButton::onMouseMove(cocos2d::EventMouse * mouseEvent)
{
	if (insideBoundingBox(cocos2d::Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY())))
	{
		if (!alreadyDrawn)
		{
			btnDrawNode->drawRect(leftPt, rightPt, cocos2d::Color4F::ORANGE);
			alreadyDrawn = true;
			alreadyClear = false;
		}
	}
	else
	{
		if (!alreadyClear)
		{
			btnDrawNode->clear();
			alreadyClear = true;
			alreadyDrawn = false;
		}
	}

	return true;
}
