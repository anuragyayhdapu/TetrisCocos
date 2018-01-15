#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    virtual bool init();
	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);
	void calcSceneDrawingData(double& u, cocos2d::Vec2& pf, cocos2d::Size size);
};
