#include "GameOverScene.h"
#include "TetrisBoardScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

bool GameOverScene::init()
{
	// super init
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();

	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);
	auto headingTxt = TetrisFont::create("game over", cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.2f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	headingTxt->write(txtDrawNode);

	// TODO: show current score, high score, and level info

	// retry button
	auto retryCallback = std::bind(&GameOverScene::retry, this, std::placeholders::_1);
	retryBtn = TetrisButton::create(retryCallback, "retry", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.65), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(retryBtn);

	// go to main menu button
	auto mainMenuCallback = std::bind(&GameOverScene::goToMainMenu, this, std::placeholders::_1);
	mainMenuBtn = TetrisButton::create(mainMenuCallback, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.50), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(mainMenuBtn);

	// quit button
	auto quitCallback = std::bind(&GameOverScene::quit, this, std::placeholders::_1);
	quitBtn = TetrisButton::create(quitCallback, "quit", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(quitBtn);

    return true;
}


void GameOverScene::retry(cocos2d::Ref *pSender)
{
	// TODO: remove hardcoded after testing
	auto scene = TetrisBoardScene::create();
	Director::getInstance()->replaceScene(scene);
}


void GameOverScene::goToMainMenu(cocos2d::Ref *pSender)
{
	auto scene = MainMenuScene::create();
	Director::getInstance()->replaceScene(scene);
}

void GameOverScene::quit(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}