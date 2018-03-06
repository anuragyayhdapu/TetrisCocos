#include "TetrisCricketInitLayer.h"
#include "TetrisFont.h"
#include "TetrisButton.h"

USING_NS_CC;

TetrisCricketInitLayer * TetrisCricketInitLayer::create(std::function<void(cocos2d::Ref*)> startFunc)
{
	auto layer = new(std::nothrow)TetrisCricketInitLayer(startFunc);
	if (layer && layer->init())
	{
		layer->autorelease();
	}
	else
	{
		delete layer;
		layer = nullptr;
	}
	return layer;
}

bool TetrisCricketInitLayer::init()
{
	auto size = Director::getInstance()->getVisibleSize();
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 128), size.width, size.height))
	{
		return false;
	}

	auto midpos = cocos2d::Vec2(size.width / 2, size.height / 2);
	addChild(TetrisButton::create(startFunc, "start", Color4F::BLUE, Vec2(midpos.x, midpos.y), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));


	return true;
}
