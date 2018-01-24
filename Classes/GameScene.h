#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:
	static cocos2d::Layer* ctLayer;

public:
	virtual bool init();
	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);
	void calcSceneDrawingData(double& u, cocos2d::Vec2& pf, cocos2d::Size size);

	void countDown(cocos2d::Size size);
	virtual void start() = 0;
	virtual void initFromDB() = 0;
	virtual void saveToDB(unsigned int, int) = 0;
};
