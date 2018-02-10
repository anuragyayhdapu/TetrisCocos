#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"
#include "TetrisButton.h"

class GameScene : public cocos2d::Scene
{
private:
	static cocos2d::Layer* ctLayer;
	static TetrisFont *ctFont;
	static cocos2d::DrawNode* ctDrawNode;
	TetrisButton* pauseBtn, stopBtn;

public:
	virtual bool init();
	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);
	void calcSceneDrawingData(double& u, cocos2d::Vec2& pf, cocos2d::Size size);
	void addButtons();

	void countDown(cocos2d::Size size);
	virtual void start() = 0;
	virtual void initFromDB() = 0;
	virtual void saveToDB() = 0;
};
