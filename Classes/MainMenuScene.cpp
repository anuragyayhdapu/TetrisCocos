#include "MainMenuScene.h"
#include "TetrisBoardScene.h"

USING_NS_CC;

bool MainMenuScene::init()
{
	// super init
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto fontDrawNode = DrawNode::create();
	this->addChild(fontDrawNode);
	auto heading = TetrisFont::create("tetris", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.8), 3.5,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	auto heading2 = TetrisFont::create("cocos", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.60), 2.5,
		FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	startBtn = TetrisButton::create(">", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.30), 3.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 1);

	heading->write(fontDrawNode);
	heading2->write(fontDrawNode);
	this->addChild(startBtn);

	// touch listners
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}


void MainMenuScene::GoToTetrisBoardScene(Ref *pSender)
{
	auto scene = TetrisBoardScene::create();
	Director::getInstance()->replaceScene(scene);
}


bool MainMenuScene::onTouchBegan(Touch* touch, Event* _event)
{
	if (startBtn->insideBoundingBox(touch->getLocation()))
	{
		GoToTetrisBoardScene(this);
	}

	return true;
}