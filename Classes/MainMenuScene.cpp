#include "MainMenuScene.h"
#include "TetrisBoardScene.h"

USING_NS_CC;

bool MainMenuScene::init()
{
	// super init
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto fontDrawNode = DrawNode::create();
	this->addChild(fontDrawNode);
	auto heading = TetrisFont::create("tetris", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.8), 3.5,
		FontColorPattern::RANDOM_BLOCK, FontAlign::MIDDLE);
	auto heading2 = TetrisFont::create("cocos", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.60), 2.5,
		FontColorPattern::RANDOM_BLOCK, FontAlign::MIDDLE);	
	startBtn = TetrisFont::create(">", Color4F::RED, Vec2(visibleSize.width / 2, visibleSize.height * 0.30), 3.5,
		FontColorPattern::RANDOM_BLOCK, FontAlign::MIDDLE);

	heading->write(fontDrawNode);
	heading2->write(fontDrawNode);
	startBtn->write(fontDrawNode);

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
	// get bounding box of play button
	if (startBtn->insideBoundingBox(touch->getLocation()))
	{
		cocos2d::log("inside play btn");
		// and move to play screen if touched
		GoToTetrisBoardScene(this);
	}

	return true;
}