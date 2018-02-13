#include "PauseScene.h"
#include "MainMenuScene.h"
#include "TetrisBoardScene.h"

USING_NS_CC;


bool PauseScene::init()
{
	// super init
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);
	auto headingTxt = TetrisFont::create("paused", cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.2f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	headingTxt->write(txtDrawNode);

	this->addButtons();

	return true;
}

PauseScene * PauseScene::create(std::string score, std::string highScore, std::string lvl)
{
	auto pauseScene = new(std::nothrow)PauseScene();
	if (pauseScene && pauseScene->init(score, highScore, lvl))
	{
		pauseScene->autorelease();
	}
	else
	{
		delete pauseScene;
		pauseScene = nullptr;
	}
	return pauseScene;
}

bool PauseScene::init(std::string score, std::string highScore, std::string lvl)
{
	if (!init())
	{
		return false;
	}

	std::string text;
	text.append("score ");
	size_t i = 0;
	while (i++ < score.length())
		text.append("  ");
	text.append("  level ");
	i = 0;
	while (i++ < lvl.length())
		text.append("  ");

	std::string nums;
	nums.append("   ");
	nums.append(score);
	nums.append("    ");
	nums.append(lvl);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);

	auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.63 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	auto scoreNums = TetrisFont::create(nums, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.65 * visibleSize.height), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);

	scoreTxt->write(txtDrawNode);
	scoreNums->write(txtDrawNode);

	return true;
}


void PauseScene::resume(cocos2d::Ref *pSender)
{
	Director::getInstance()->popScene();
}


void PauseScene::retry(cocos2d::Ref *pSender)
{
	// TODO: remove hardcoded after testing
	auto scene = TetrisBoardScene::create();
	Director::getInstance()->replaceScene(scene);
}


void PauseScene::goToMainMenu(cocos2d::Ref *pSender)
{
	Director::getInstance()->popScene();
	auto scene = MainMenuScene::create();
	Director::getInstance()->replaceScene(scene);
}

void PauseScene::addButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// resume button
	auto resumeCallback = std::bind(&PauseScene::resume, this, std::placeholders::_1);
	resumeBtn = TetrisButton::create(resumeCallback, "resume", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.50), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(resumeBtn);

	// retry button
	auto retryCallback = std::bind(&PauseScene::retry, this, std::placeholders::_1);
	retryBtn = TetrisButton::create(retryCallback, "retry", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(retryBtn);

	// go to main menu button
	auto mainMenuCallback = std::bind(&PauseScene::goToMainMenu, this, std::placeholders::_1);
	mainMenuBtn = TetrisButton::create(mainMenuCallback, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.20), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(mainMenuBtn);

}
