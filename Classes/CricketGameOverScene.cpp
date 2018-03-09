#include "CricketGameOverScene.h"
#include "TetrisButton.h"
#include "TetrisCricketBoardScene.h"
#include "MainMenuScene.h"


USING_NS_CC;

CricketGameOverScene * CricketGameOverScene::create(std::string score, std::string winPlayerName)
{
	auto scene = new(std::nothrow)CricketGameOverScene(score, winPlayerName);
	if (scene && scene->init())
	{
		scene->autorelease();
	}
	else
	{
		delete scene;
		scene = nullptr;
	}
	return scene;
}

bool CricketGameOverScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// draw heading
	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);
	auto headingTxt = TetrisFont::create("game over", cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.2f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	headingTxt->write(txtDrawNode);

	// draw custom message
	std::string text(winPlayerName);
	text.append(" won by ");
	text.append(score);
	text.append(" runs");
	auto scoreTxt = TetrisFont::create(text, cocos2d::Color4F::GRAY, Vec2(visibleSize.width * 0.5, 0.63 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	scoreTxt->write(txtDrawNode);


	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(TetrisCricketBoardScene::create());
	}, "rematch", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.40), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7));

	addChild(TetrisButton::create([](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(MainMenuScene::create());
	}, "menu", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 7));

	return true;
}