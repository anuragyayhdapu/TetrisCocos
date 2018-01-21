#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    virtual bool init();
	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);
	void calcSceneDrawingData(double& u, cocos2d::Vec2& pf, cocos2d::Size size);
	void countDown(cocos2d::Size size, cocos2d::Layer* layer);
	void count3(float);
	void count2(float);
	void count1(float);

	virtual void start() = 0;
};
