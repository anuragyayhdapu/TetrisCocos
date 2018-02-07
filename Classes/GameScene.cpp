#include "GameScene.h"
#include "TetrisBoardScene.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Layer *GameScene::ctLayer;
TetrisFont *GameScene::ctFont;
cocos2d::DrawNode *GameScene::ctDrawNode;

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

	ctDrawNode = DrawNode::create();
	this->addChild(ctDrawNode, 0, DRAW_NODE);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	ctFont = TetrisFont::create("3", Color4F::BLUE, Vec2(visibleSize.width * 0.45, visibleSize.height * 0.6), 5, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	this->addChild(ctFont, 0, TETRIS_FONT);

	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(CallFunc::create([&] {
		auto font = this->getChildByTag<TetrisFont*>(TETRIS_FONT);
		auto drawNode = this->getChildByTag<DrawNode*>(DRAW_NODE);
		font->write(drawNode);
	}));
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		auto font = this->getChildByTag<TetrisFont*>(TETRIS_FONT);
		auto drawNode = this->getChildByTag<DrawNode*>(DRAW_NODE);
		font->reWrite("2", drawNode);
	}));
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		auto font = this->getChildByTag<TetrisFont*>(TETRIS_FONT);
		auto drawNode = this->getChildByTag<DrawNode*>(DRAW_NODE);
		font->reWrite("1", drawNode);
	}));
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		auto font = this->getChildByTag<TetrisFont*>(TETRIS_FONT);
		auto drawNode = this->getChildByTag<DrawNode*>(DRAW_NODE);
		font->reWrite("go", drawNode);
	}));
	actions.pushBack(DelayTime::create(1.0));
	actions.pushBack(CallFunc::create([&] {
		this->removeChild(ctDrawNode);
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


void GameScene::GoToPauseScene(cocos2d::Ref *pSender)
{
	auto scene = PauseScene::create();
	Director::getInstance()->pushScene(scene);
}


void GameScene::GoToGameOverScene(cocos2d::Ref *pSender)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(scene);
}