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
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 240), size.width, size.height))
	{
		return false;
	}

	auto midpos = cocos2d::Vec2(size.width / 2, size.height / 2);
	addChild(TetrisButton::create(startFunc, "play", Color4F::BLUE, Vec2(midpos.x, size.height * 0.3), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	DrawNode *txtDrawNode;
	addChild(txtDrawNode = DrawNode::create());

	addChild(TetrisFont::create("first inning", txtDrawNode, Color4F::ORANGE, Vec2(midpos.x, size.height * 0.8), 1.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(TetrisFont::create("player1", txtDrawNode, Color4F::GRAY, Vec2(midpos.x, size.height * 0.6), 0.8f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(TetrisFont::create("player2", txtDrawNode, Color4F::GRAY, Vec2(midpos.x, size.height * 0.5), 0.8f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(TetrisFont::create("bowling", txtDrawNode, Color4F::ORANGE, Vec2(size.width * 0.53, size.height * 0.6), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));
	addChild(TetrisFont::create("batting", txtDrawNode, Color4F::ORANGE, Vec2(size.width * 0.53, size.height * 0.5), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));

	return true;
}
