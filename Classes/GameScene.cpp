#include "GameScene.h"
#include "TetrisBoardScene.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Layer *GameScene::ctLayer;
TetrisButton *GameScene::ctFont;

#define DRAW_NODE 1
#define TETRIS_FONT 2


void GameScene::calcSceneDrawingData(double & u, cocos2d::Vec2 & pf, cocos2d::Size size)
{
	// calculate _u, _pl, _pf
	double y = size.height, x = size.width;
	u = 0;
	if (size.height < size.width)
	{
		u = y / t_const::NUM_OF_UNIT_BLOCKS_IN_HEIGHT;
		x = u * t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH;
	}
	else if (size.height >= size.width)
	{
		u = x / t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH;
		y = u * t_const::NUM_OF_UNIT_BLOCKS_IN_HEIGHT;
	}

	double xd = size.width - x;
	double yd = size.height - y;

	auto pl = Vec2(xd / 2, (yd / 2) + y); // shifting this point from bottom left to top left
	pf = Vec2(pl.x + u / 2, pl.y - u / 2);
}

void GameScene::countDown(Size size)
{
	ctLayer = LayerColor::create(Color4B(0, 0, 0, 128), size.width, size.height);
	ctLayer->setPosition(Vec2(0, 0));
	this->addChild(ctLayer);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	ctFont = TetrisButton::create([] (cocos2d::Ref*){}, "3", Color4F::BLUE, Vec2(visibleSize.width * 0.45, visibleSize.height * 0.6), 5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID);
	ctFont->nonInteractive = true;
	this->addChild(ctFont, 0, TETRIS_FONT);

	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		auto btn = this->getChildByTag<TetrisButton*>(TETRIS_FONT);
		btn->reWrite("2");
	}));
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		auto btn = this->getChildByTag<TetrisButton*>(TETRIS_FONT);
		btn->reWrite("1");
	}));
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		this->removeChild(ctFont);
		this->removeChild(ctLayer);
		this->start();
	}));

	auto sequence = Sequence::create(actions);
	this->runAction(sequence);
}


bool GameScene::init()
{
	// super init
	if (!Scene::init())
	{
		return false;
	}

	return true;
}


void GameScene::addButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto pauseCallBack = std::bind(&GameScene::GoToPauseScene, this, std::placeholders::_1);
	pauseBtn = TetrisButton::create(pauseCallBack, "p", Color4F::RED, Vec2(visibleSize.width * 0.20, visibleSize.height * 0.95), 1.5, FontAlign::RIGHT, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID);
	this->addChild(pauseBtn);

	auto stopCallBack = std::bind(&GameScene::GoToGameOverScene, this, std::placeholders::_1);
	pauseBtn = TetrisButton::create(stopCallBack, "x", Color4F::RED, Vec2(visibleSize.width * 0.10, visibleSize.height * 0.95), 1.5, FontAlign::RIGHT, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID);
	this->addChild(pauseBtn);
}


void GameScene::GoToPauseScene(cocos2d::Ref *pSender)
{
	auto prevScene = static_cast<TetrisBoardScene*>(pSender);

	auto scene = PauseScene::create(prevScene->getScore(), prevScene->getHighScore(), prevScene->getLevel());
	Director::getInstance()->pushScene(scene);
}


void GameScene::GoToGameOverScene(cocos2d::Ref *pSender)
{
	auto prevScene = static_cast<TetrisBoardScene*>(pSender);

	auto scene = GameOverScene::create(prevScene->getScore(), prevScene->getHighScore(), prevScene->getLevel());
	Director::getInstance()->replaceScene(scene);
}