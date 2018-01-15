#include "GameScene.h"
#include "TetrisBoardScene.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"

USING_NS_CC;


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

bool GameScene::init()
{
	// super init
    if ( !Scene::init() )
    {
        return false;
    }

    return true;
}


void GameScene::GoToPauseScene(cocos2d::Ref *pSender)
{
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void GameScene::GoToGameOverScene(cocos2d::Ref *pSender)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(scene);
}