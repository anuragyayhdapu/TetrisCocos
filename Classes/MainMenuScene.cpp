#include "MainMenuScene.h"
#include "TetrisBoardScene.h"
#include "TetrisFont.h"

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
	auto startBtn = TetrisFont::create("play", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.53), 2.5,
		FontColorPattern::RANDOM_WORD, FontAlign::MIDDLE);	
	auto quitBtn = TetrisFont::create("quit", Color4F::BLUE, Vec2(visibleSize.width / 2, visibleSize.height * 0.35), 2.5,
		FontColorPattern::RANDOM_WORD, FontAlign::MIDDLE);

	heading->write(fontDrawNode);
	startBtn->write(fontDrawNode);
	quitBtn->write(fontDrawNode);

    
    return true;
}


void MainMenuScene::GoToTetrisBoardScene(Ref *pSender)
{
	/*auto scene = TetrisBoardScene::createTetrisBoardScene();
	Director::getInstance()->replaceScene(scene);*/
}