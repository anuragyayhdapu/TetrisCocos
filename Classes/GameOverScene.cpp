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

	drawButtons();

    return true;
}

GameOverScene * GameOverScene::create(std::string score, std::string highScore, std::string lvl)
{
	auto overScene = new(std::nothrow)GameOverScene();
	if (overScene && overScene->init(score, highScore, lvl))
	{
		overScene->autorelease();
	}
	else
	{
		delete overScene;
		overScene = nullptr;
	}
	return overScene;
}

bool GameOverScene::init(std::string score, std::string highScore, std::string lvl)
{
	if (!init())
		return false;

	// TODO: add custom message based on score and high score

	std::string text;
	text.append("score ");
	size_t i = 0;
	while (i++ < score.length())
		text.append(" ");

	std::string nums;
	nums.append("      "); // 5
	nums.append(score);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);

	auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.65 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	auto scoreNums = TetrisFont::create(nums, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.65 * visibleSize.height), 0.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);

	scoreTxt->write(txtDrawNode);
	scoreNums->write(txtDrawNode);

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

void GameOverScene::drawButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// retry button
	auto retryCallback = std::bind(&GameOverScene::retry, this, std::placeholders::_1);
	retryBtn = TetrisButton::create(retryCallback, "retry", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.40), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(retryBtn);

	// go to main menu button
	auto mainMenuCallback = std::bind(&GameOverScene::goToMainMenu, this, std::placeholders::_1);
	mainMenuBtn = TetrisButton::create(mainMenuCallback, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(mainMenuBtn);
}
