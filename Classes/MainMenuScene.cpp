#include "MainMenuScene.h"
#include "TetrisBoardScene.h"
#include "LocalMultiplayerMenuScene.h"
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
	this->addChild(fontDrawNode);
	auto heading = TetrisFont::create("tetris", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.8), 3.5f,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	cocos2d::log(std::to_string(heading->getLeftPt().y).c_str());
	cocos2d::log(std::to_string(visibleSize.height).c_str());
	
	heading->write(fontDrawNode);
	
	auto heading2 = TetrisFont::create("cocos", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.6), 2.5f,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	heading2->write(fontDrawNode);

	auto btnCallbackFunc = std::bind(&MainMenuScene::GoToSinglePlayerScene, this, std::placeholders::_1);
	spStartBtn = TetrisButton::create(btnCallbackFunc, "alone", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.30), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 3);
	this->addChild(spStartBtn);

	// local multiplayer 
	lmStartBtn = TetrisButton::create([](Ref*) {
		Director::getInstance()->replaceScene(LocalMultiPlayerMenuScene::create());
	}, "together", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.15), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 3);
	this->addChild(lmStartBtn);



	return true;
}


void MainMenuScene::GoToSinglePlayerScene(Ref *pSender)
{
	auto scene = TetrisBoardScene::create();
	Director::getInstance()->replaceScene(scene);
}