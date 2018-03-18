#include "MultiplayerTypeMenuScene.h"
#include "LocalMultiplayerMenuScene.h"
#include "NetworkTetrisBoardScene.h"
#include "TetrisButton.h"

USING_NS_CC;

bool MultiplayerTypeMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);
	addChild(TetrisFont::create("select", txtDrawNode, cocos2d::Color4F::ORANGE, Vec2(visibleSize.width * 0.5, 0.9 * visibleSize.height), 2.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(TetrisFont::create("type", txtDrawNode, cocos2d::Color4F::ORANGE, Vec2(visibleSize.width * 0.5, 0.75 * visibleSize.height), 1.8f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));

	// network
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(NetworkTetrisBoardScene::create());
	}, "network", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.40), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// local
	addChild(TetrisButton::create([&](cocos2d::Ref*) {
		Director::getInstance()->replaceScene(LocalMultiPlayerMenuScene::create());
	}, "local", Color4F::RED, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25), 1.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	return true;
}
