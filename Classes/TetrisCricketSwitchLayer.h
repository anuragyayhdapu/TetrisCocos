#pragma once

#include "cocos2d.h"
#include <functional>

class TetrisCricketSwitchLayer : public cocos2d::LayerColor
{
public:
	TetrisCricketSwitchLayer(std::function<void(cocos2d::Ref*)> startFunc, std::string scoreToChase) : startFunc(startFunc), scoreToChase(scoreToChase) {}
	virtual ~TetrisCricketSwitchLayer(){}

	static TetrisCricketSwitchLayer* create(std::function<void(cocos2d::Ref*)>, std::string scoreToChase);
private:
	virtual bool init();
	std::function<void(cocos2d::Ref*)> startFunc;
	std::string scoreToChase;
};