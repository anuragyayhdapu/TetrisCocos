#include "LocalGameOverScene.h"
#include "LocalTetrisBoardScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

LocalGameOverScene * LocalGameOverScene::create(std::string winPlayerName, std::string winScoreDelta, MultiplayerGameMode gameMode)
{
	auto overScene = new(std::nothrow)LocalGameOverScene(gameMode);
	if (overScene && overScene->init(winPlayerName, winScoreDelta))
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

LocalGameOverScene * LocalGameOverScene::create(std::string drawScore, MultiplayerGameMode gameMode)
{
	auto overScene = new(std::nothrow)LocalGameOverScene(gameMode);
	if (overScene && overScene->init(drawScore))
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

bool LocalGameOverScene::init(std::string winPlayerName, std::string winScoreDelta)
{
	if (!Scene::init())
	{
		return false;
	}

	heading();
	winMessage(winPlayerName, winScoreDelta);
	buttons();

	return true;
}

bool LocalGameOverScene::init(std::string drawScore)
{
	if (!Scene::init())
	{
		return false;
	}

	heading();
	drawMessage(drawScore);
	buttons();

	return true;
}

void LocalGameOverScene::heading()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// draw heading
	txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);
	auto headingTxt = TetrisFont::create("game over", cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.2f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	headingTxt->write(txtDrawNode);
}

void LocalGameOverScene::buttons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// rematch button
	rematchBtn = TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalTetrisBoardScene::create(this->gameMode));
	}, "rematch", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.40), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(rematchBtn);

	// main menu button
	mainMenuBtn = TetrisButton::create([](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(MainMenuScene::create());
	}, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7);
	this->addChild(mainMenuBtn);
}

void LocalGameOverScene::drawMessage(std::string drawScore)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	std::string text;
	text.append("draw by ");
	text.append(drawScore);
	text.append(" pts");
	auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.63 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	scoreTxt->write(txtDrawNode);
}

void LocalGameOverScene::winMessage(std::string winPlayerName, std::string winScoreDelta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// winning message
	if (gameMode != MultiplayerGameMode::LAST_MAN_STANDING)
	{
		std::string text;
		text.append(winPlayerName);
		text.append(" player won by ");
		size_t i = 0;
		while (i++ < winScoreDelta.length())
			text.append("  ");
		text.append(" pts");

		std::string nums;
		nums.append(winScoreDelta);
		nums.append("  ");

		auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.63 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
		auto scoreNums = TetrisFont::create(nums, cocos2d::Color4F::GRAY, Vec2(scoreTxt->getRightPt().x, scoreTxt->getRightPt().y + 0.05 * scoreTxt->getRightPt().y), 1.0f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::RIGHT);

		scoreTxt->write(txtDrawNode);
		scoreNums->write(txtDrawNode);
	}
	else
	{
		std::string text;
		text.append(winPlayerName);
		text.append(" player won");
		auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.63 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
		scoreTxt->write(txtDrawNode);
	}
}