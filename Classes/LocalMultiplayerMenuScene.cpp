#include "LocalMultiplayerMenuScene.h"
#include "LocalTetrisBoardScene.h"
#include "MainMenuScene.h"
#include "TetrisCricketBoardScene.h"

USING_NS_CC;

bool LocalMultiPlayerMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);
	addChild(TetrisFont::create("select", txtDrawNode, cocos2d::Color4F::ORANGE, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(TetrisFont::create("mode", txtDrawNode, cocos2d::Color4F::ORANGE, Vec2(visibleSize.width * 0.5, 0.75 * visibleSize.height), 1.8f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));

	// last man standing
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::LAST_MAN_STANDING));
	}, "infinite", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.36), 1.2f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// all about score
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::ALL_ABOUT_SCORE));
	}, "scoring", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.23), 1.2f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// race against time
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::RACE_AGAINS_TIME, 2));
	}, "time pass", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.10), 1.2f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// cricket
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(TetrisCricketBoardScene::create());
	}, "cricket", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.49), 1.2f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	return true;
}
