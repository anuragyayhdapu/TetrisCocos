#pragma once

#include "cocos2d.h"
#include "TetrisButton.h"
#include "Observer.h"
#include "message.pb.h"

class GameScene : public cocos2d::Scene, public Observer
{
private:
	static cocos2d::Layer* ctLayer;
	static TetrisButton *ctFont;
	TetrisButton* pauseBtn;

public:
	virtual bool init();
	void GoToPauseScene(cocos2d::Ref * pSender);
	void GoToGameOverScene(cocos2d::Ref * pSender);
	void calcSceneDrawingData(double& u, cocos2d::Vec2& pf, cocos2d::Size size, int numOfUnitBlocksInHeight, int numOfUnitBlocksInWidth);
	void addButtons();

	void countDown(cocos2d::Size size);
	virtual void start() = 0;
	virtual void initFromDB() {}
	virtual void saveToDB() {}

	virtual void onNetworkNotify(const tetris::proto::Board&, t_network::Messagetype) { /*DO NOTHING*/ }
};
