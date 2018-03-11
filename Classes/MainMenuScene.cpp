#include "MainMenuScene.h"
#include "TetrisBoardScene.h"
#include "LocalMultiplayerMenuScene.h"
#include "TetrisButton.h"
#include "TetrisCricketBoardScene.h"
#include <functional>

USING_NS_CC;

bool MainMenuScene::init()
{
	// super init
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto fontDrawNode = DrawNode::create();
	addChild(fontDrawNode);

	addChild(TetrisFont::create("tetris", fontDrawNode, Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.8), 3.5f,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	
	addChild(TetrisFont::create("cocos", fontDrawNode, Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.6), 2.5f,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));

	// single player
	addChild(TetrisButton::create([](Ref*) {
		//auto scene = TetrisBoardScene::create();

		Director::getInstance()->replaceScene(TetrisCricketBoardScene::create(CricketInnings::FIRST_INIINGS));
	}, "alone", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.30), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 3));

	// local multiplayer 
	addChild(TetrisButton::create([](Ref*) {
		Director::getInstance()->replaceScene(LocalMultiPlayerMenuScene::create());
	}, "together", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.15), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 3));

	return true;
}