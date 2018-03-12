#pragma once

#include "cocos2d.h"
#include "Constants.h"

class CricketPauseScene : public cocos2d::Scene
{
public:
	CricketPauseScene(CricketInnings inning) : inning(inning) {}
	static CricketPauseScene * CricketPauseScene::create(CricketInnings inning);
	virtual ~CricketPauseScene() {}

private:
	virtual bool init();
	CricketInnings inning;
};