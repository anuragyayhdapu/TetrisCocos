#include "TetrisCricketSwitchLayer.h"
#include "TetrisFont.h"
#include "TetrisButton.h"

USING_NS_CC;

TetrisCricketSwitchLayer * TetrisCricketSwitchLayer::create(std::function<void(cocos2d::Ref*)> startFunc, int scoreToChase)
{
	auto layer = new(std::nothrow)TetrisCricketSwitchLayer(startFunc, scoreToChase);
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

bool TetrisCricketSwitchLayer::init()
{
	auto size = Director::getInstance()->getVisibleSize();
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 240), size.width, size.height))
	{
		return false;
	}

	auto midpos = cocos2d::Vec2(size.width / 2, size.height / 2);
	addChild(TetrisButton::create(startFunc, "play", Color4F::BLUE, Vec2(midpos.x, size.height * 0.25), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	TetrisFont *p1, *p2, *s1, *s2, *t1, *t2, *h;
	DrawNode *txtDrawNode;

	addChild(txtDrawNode = DrawNode::create());
	addChild(h = TetrisFont::create("second inning", Color4F::ORANGE, Vec2(midpos.x, size.height * 0.8), 1.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));

	addChild(s1 = TetrisFont::create("score to chase", Color4F::GRAY, Vec2(midpos.x, size.height * 0.58), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(s2 = TetrisFont::create(std::to_string(scoreToChase), Color4F::ORANGE, Vec2(size.width * 0.53, size.height * 0.6), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::LEFT));
	
	addChild(p1 = TetrisFont::create("player1", Color4F::GRAY, Vec2(midpos.x, size.height * 0.5), 0.8f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(p2 = TetrisFont::create("player2", Color4F::GRAY, Vec2(midpos.x, size.height * 0.4), 0.8f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(t2 = TetrisFont::create("batting", Color4F::ORANGE, Vec2(size.width * 0.53, size.height * 0.5), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));
	addChild(t1 = TetrisFont::create("bowling", Color4F::ORANGE, Vec2(size.width * 0.53, size.height * 0.4), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));




	h->write(txtDrawNode);
	p1->write(txtDrawNode);
	p2->write(txtDrawNode);
	t1->write(txtDrawNode);
	t2->write(txtDrawNode);
	s1->write(txtDrawNode);
	s2->write(txtDrawNode);
	return true;
}
