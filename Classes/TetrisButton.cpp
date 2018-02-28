#include "TetrisButton.h"
#include "TetrominoTemplates.h"

USING_NS_CC;

TetrisButton::TetrisButton(std::function<void(cocos2d::Ref*)> _btnCallbackFunc, cocos2d::Color4F borderColor)
	:
	btnCallbackFunc(_btnCallbackFunc),
	borderColor(borderColor),
	alreadyClear(true),
	alreadyDrawn(false),
	curr(&s),
	nonInteractive(false),
	animating(false)
{
}

TetrisButton::~TetrisButton()
{
}


TetrisButton * TetrisButton::create(std::string text, cocos2d::Vec2 position, float size, cocos2d::Color4F borderColor, FontAlign align)
{
	TetrisButton* ptr = new(std::nothrow)TetrisButton([](cocos2d::Ref*) {}, borderColor);
	ptr->nonInteractive = true;
	if (ptr && ptr->init(text, position, size, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, align, /*padding*/0))
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


TetrisButton * TetrisButton::create(std::function<void(cocos2d::Ref*)> _btnCallbackFunc, std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontAlign align, FontColorPattern colorPattern, FontDrawPattern drawPattern, float width)
{
	TetrisButton* ptr = new(std::nothrow)TetrisButton(_btnCallbackFunc, color);
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

	// draw using primary
	p = cocos2d::DrawNode::create();
	this->addChild(p);
	this->font = TetrisFont::create(text, this->borderColor, position, size, colorPattern, drawPattern, align);
	this->addChild(font);
	font->write(p);

	// initialize rand animate list
	s = cocos2d::DrawNode::create();
	this->addChild(s);
	createRandList();

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
	if (diff > 1)
		rightPt.x += offset;
	rightPt.y -= size * TetrisFont::u;

	btnDrawNode = cocos2d::DrawNode::create();
	this->addChild(btnDrawNode);

	auto mouseListner = cocos2d::EventListenerMouse::create();
	mouseListner->onMouseMove = CC_CALLBACK_1(TetrisButton::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TetrisButton::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TetrisButton::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	startAnimate();

	return true;
}


bool TetrisButton::insideBoundingBox(cocos2d::Vec2 pos)
{
	if (nonInteractive)
		return false;

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
			stopAnimate();
			drawBorder();
			alreadyDrawn = true;
			alreadyClear = false;
		}
	}
	else
	{
		if (!alreadyClear)
		{
			startAnimate();
			btnDrawNode->clear();
			alreadyClear = true;
			alreadyDrawn = false;
		}
	}

	return true;
}

bool TetrisButton::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * _event)
{
	if (insideBoundingBox(touch->getLocation()))
	{
		cocos2d::log("Button Click started");
		return true;
	}
	return false;
}

bool TetrisButton::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * _event)
{
	if (insideBoundingBox(touch->getLocation()))
	{
		cocos2d::log("Button Click stoped");
		this->btnCallbackFunc(this->getParent());
		return true;
	}
	else
	{
		cocos2d::log("went outside");
	}
	return false;
}


void TetrisButton::startAnimate()
{
	animating = true;
	schedule(CC_SCHEDULE_SELECTOR(TetrisButton::animate));
}


void TetrisButton::stopAnimate()
{
	animating = false;
	unschedule(CC_SCHEDULE_SELECTOR(TetrisButton::animate));
}


void TetrisButton::animate(float dt)
{
	if (rIter != randList.end())
	{
		// get random color
		auto color = cocos2d::Color4F(TetrominoTemplate::colorTemplates->at(rand() % TetrominoTemplate::size));
		auto pos = *rIter;
		++rIter;

		// draw 
		font->drawBlock(*curr, pos, color);
	}
	else
	{
		// switch animate node
		(*curr)->setLocalZOrder(-1);
		if (*curr == p)
			curr = &s;
		else
			curr = &p;

		(*curr)->clear();
		(*curr)->setLocalZOrder(0);
		createRandList();
	}

}


void TetrisButton::createRandList()
{
	randList.clear();

	for (size_t i = 0; i < font->fontBlocksDD.size(); i++)
		randList.push_back(i);

	// rearrange randomely
	for (size_t i = 0; i < font->fontBlocksDD.size() - 1; i++)
	{
		// get rand pos between i and size
		//auto r = i + int((rand() * (font->fontBlocksDD.size() - i)) / (RAND_MAX + 1.0));
		auto r = rand() % (font->fontBlocksDD.size() - i);

		// swap a[i] to a[r]
		auto temp = randList[i];
		randList[i] = randList[i + r];
		randList[i + r] = temp;
	}

	rIter = randList.begin();
}


void TetrisButton::reWrite(std::string text)
{
	stopAnimate();
	(*curr)->clear();
	font->reWrite(text, *curr);
	createRandList();
	startAnimate();
}

void TetrisButton::freeze()
{
	if (animating)
	{
		stopAnimate();
		removeBorder();
	}
}
