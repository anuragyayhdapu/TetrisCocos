#include "PauseScene.h"
#include "MainMenuScene.h"
#include "TetrisBoardScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);

    return scene;
}


bool PauseScene::init()
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


void PauseScene::Resume(cocos2d::Ref *pSender)
{
	Director::getInstance()->popScene();
}


void PauseScene::GoToMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}


void PauseScene::Retry(cocos2d::Ref *pSender)
{
	/*auto scene = TetrisBoardScene::createTetrisBoardScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);*/
}