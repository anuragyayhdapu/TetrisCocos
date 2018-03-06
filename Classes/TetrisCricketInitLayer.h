#pragma once

#include "cocos2d.h"
#include <functional>

class TetrisCricketInitLayer : public cocos2d::LayerColor
{
public:
	TetrisCricketInitLayer(std::function<void(cocos2d::Ref*)> startFunc) : startFunc(startFunc) {}
	virtual ~TetrisCricketInitLayer(){}

	static TetrisCricketInitLayer* create(std::function<void(cocos2d::Ref*)>);
private:
	virtual bool init();
	std::function<void(cocos2d::Ref*)> startFunc;
};