#pragma once

#include "cocos2d.h"
#include "Constants.h"

class LocalGameOverScene : public cocos2d::Scene
{
public:
	LocalGameOverScene(MultiplayerGameMode gameMode) : gameMode(gameMode) {}
	virtual ~LocalGameOverScene() {}
	static LocalGameOverScene* create(std::string winPlayerName, std::string winScoreDelta, MultiplayerGameMode gameMode);
	static LocalGameOverScene* create(std::string drawScore, MultiplayerGameMode gameMode);

private:
	virtual bool init(std::string winPlayerName, std::string winScoreDelta);
	virtual bool init(std::string drawScore);
	MultiplayerGameMode gameMode;
	cocos2d::DrawNode* txtDrawNode;

	void heading();
	void buttons();
	void drawMessage(std::string darwScore);
	void winMessage(std::string winPlayerName, std::string winScoreDelta);
};