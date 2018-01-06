#include "MainMenuScene.h"
#include "TetrisBoardScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);

    return scene;
}


bool MainMenuScene::init()
{
	// super init
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}


void MainMenuScene::GoToTetrisBoardScene(Ref *pSender)
{
	auto scene = TetrisBoardScene::createTetrisBoardScene();
	Director::getInstance()->replaceScene(scene);
}