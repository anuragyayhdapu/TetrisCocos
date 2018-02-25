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
	auto headingTxt = TetrisFont::create("select mode", cocos2d::Color4F::ORANGE, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 1.8f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	headingTxt->write(txtDrawNode);


	lastManStandingBtn = TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::LAST_MAN_STANDING));
	}, "last man standing", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.50), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 20);
	this->addChild(lastManStandingBtn);

	allAboutScoreBtn = TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::ALL_ABOUT_SCORE));
	}, "all about score", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.40), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 20);
	this->addChild(allAboutScoreBtn);

	raceAgainstTimeBtn = TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(MultiplayerGameMode::RACE_AGAINS_TIME, 2));
	}, "time race", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.30), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 20);
	this->addChild(raceAgainstTimeBtn);

	backBtn = TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(MainMenuScene::create());
	}, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.20), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 20);
	this->addChild(backBtn);

	return true;
}
