#pragma once

#include "cocos2d.h"

class CricketGameOverScene : public cocos2d::Scene
{
public:
	virtual ~CricketGameOverScene() {}
	CricketGameOverScene(int score, std::string winPlayerName) : score(score), winPlayerName(winPlayerName) {}

	static CricketGameOverScene* create(int score, std::string winPlayerName);
	virtual bool init();

private:
	int score;
	std::string winPlayerName;
};