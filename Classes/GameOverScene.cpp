#include "GameOverScene.h"
#include "TetrisBoardScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);

    return scene;
}


bool GameOverScene::init()
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


void GameOverScene::GoToTetrisBoardScene(cocos2d::Ref *pSender)
{
	/*auto scene = TetrisBoardScene::createTetrisBoardScene();
	Director::getInstance()->replaceScene(scene);*/
}


void GameOverScene::GoToMainMenuScene(cocos2d::Ref *pSender)
{
	/*auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);*/
}