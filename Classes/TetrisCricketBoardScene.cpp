#include "TetrisCricketBoardScene.h"

USING_NS_CC;

bool TetrisCricketBoardScene::init()
{
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->calcSceneDrawingData(_u, _pf, visibleSize, t_const::cr::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::cr::NUM_OF_UNIT_BLOCKS_IN_WIDTH);

	initDrawNodes();

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisCricketBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	//initBowlingList();

	// add boards



	return true;
}

void TetrisCricketBoardScene::initDrawNodes()
{
	addChild(windowDrawNode = DrawNode::create());
}


void TetrisCricketBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{

	default: break;

	}
}