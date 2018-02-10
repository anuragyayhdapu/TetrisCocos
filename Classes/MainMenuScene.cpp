#include "MainMenuScene.h"
#include "TetrisBoardScene.h"
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
	auto heading = TetrisFont::create("tetris", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.8), 3.5,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	heading->write(fontDrawNode);
	
	auto heading2 = TetrisFont::create("cocos", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.60), 2.5,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	heading2->write(fontDrawNode);

	auto btnCallbackFunc = std::bind(&MainMenuScene::GoToSinglePlayerScene, this, std::placeholders::_1);
	spStartBtn = TetrisButton::create(btnCallbackFunc, ">", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.30), 3.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 3);
	this->addChild(spStartBtn);

	return true;
}


void MainMenuScene::GoToSinglePlayerScene(Ref *pSender)
{
	auto scene = TetrisBoardScene::create();
	Director::getInstance()->replaceScene(scene);
}