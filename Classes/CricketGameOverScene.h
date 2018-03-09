#pragma once

#include "cocos2d.h"

class CricketGameOverScene : public cocos2d::Scene
{
public:
	virtual ~CricketGameOverScene() {}
	CricketGameOverScene(std::string score, std::string winPlayerName) : score(score), winPlayerName(winPlayerName) {}

	static CricketGameOverScene* create(std::string score, std::string winPlayerName);
	virtual bool init();

private:
	std::string score, winPlayerName;
};