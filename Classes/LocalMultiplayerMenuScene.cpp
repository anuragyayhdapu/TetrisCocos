#include "LocalMultiplayerMenuScene.h"
#include "LocalTetrisBoardScene.h"
#include "MainMenuScene.h"

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
	}, "infinite", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.50), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// all about score
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::ALL_ABOUT_SCORE));
	}, "sirf score", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// race against time
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::RACE_AGAINS_TIME, 2));
	}, "time pass", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.20), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// not really needed
	/*backBtn = TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(MainMenuScene::create());
	}, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.20), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 20);
	this->addChild(backBtn);*/

	return true;
}
