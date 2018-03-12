#include "CricketPauseScene.h"
#include "TetrisButton.h"
#include "TetrisCricketBoardScene.h"
#include "MainMenuScene.h"

USING_NS_CC;


CricketPauseScene * CricketPauseScene::create(CricketInnings inning)
{
	auto pauseScene = new(std::nothrow)CricketPauseScene(inning);
	if (pauseScene && pauseScene->init())
	{
		pauseScene->autorelease();
	}
	else
	{
		delete pauseScene;
		pauseScene = nullptr;
	}
	return pauseScene;
}

bool CricketPauseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto txtDrawNode = DrawNode::create();
	addChild(txtDrawNode);

	// heading
	addChild(TetrisFont::create("paused", txtDrawNode, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.2f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));

	std::string text;
	if (inning == CricketInnings::FIRST_INIINGS)
		text = "first inning";
	else
		text = "second inning";

	addChild(TetrisFont::create(text, txtDrawNode, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.65 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE));

	// resume
	addChild(TetrisButton::create([&](Ref*) {
		Director::getInstance()->popScene();
	}, "resume", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.50), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7));

	// rematch
	addChild(TetrisButton::create([&](Ref*) {
		Director::getInstance()->replaceScene(TetrisCricketBoardScene::create());
	}, "rematch", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 2));

	// menu
	addChild(TetrisButton::create([&](Ref*) {
		Director::getInstance()->popScene();
		Director::getInstance()->replaceScene(MainMenuScene::create());
	}, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.20), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7));

	return true;
}
