#include "LocalPauseScene.h"
#include "LocalTetrisBoardScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

LocalPauseScene * LocalPauseScene::create(std::string p1Score, std::string p2Score)
{
	auto pauseScene = new(std::nothrow)LocalPauseScene();
	if (pauseScene && pauseScene->init(p1Score, p2Score))
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

bool LocalPauseScene::init(std::string p1Score, std::string p2Score)
{
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

	std::string text;
	text.append("left  ");
	size_t i = 0;
	while (i++ < p1Score.length())
		text.append("  ");
	text.append("  right ");
	i = 0;
	while (i++ < p2Score.length())
		text.append("  ");

	std::string nums;
	nums.append("   ");
	nums.append(p1Score);
	nums.append("    ");
	nums.append(p2Score);

	auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.63 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	auto scoreNums = TetrisFont::create(nums, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.65 * visibleSize.height), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);

	scoreTxt->write(txtDrawNode);
	scoreNums->write(txtDrawNode);

	return true;
}

void LocalPauseScene::goBack(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

void LocalPauseScene::rematch(cocos2d::Ref * pSender)
{
	auto scene = LocalTetrisBoardScene::create();
	Director::getInstance()->replaceScene(scene);
}

void LocalPauseScene::goToMainMenu(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(MainMenuScene::create());
}

void LocalPauseScene::addButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// resume button
	auto resumeCallback = std::bind(&LocalPauseScene::goBack, this, std::placeholders::_1);
	resumeBtn = TetrisButton::create(resumeCallback, "resume", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.50), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(resumeBtn);

	// retry button
	auto retryCallback = std::bind(&LocalPauseScene::rematch, this, std::placeholders::_1);
	rematchBtn = TetrisButton::create(retryCallback, "rematch", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(rematchBtn);

	// go to main menu button
	auto mainMenuCallback = std::bind(&LocalPauseScene::goToMainMenu, this, std::placeholders::_1);
	mainMenuBtn = TetrisButton::create(mainMenuCallback, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.20), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(mainMenuBtn);

}