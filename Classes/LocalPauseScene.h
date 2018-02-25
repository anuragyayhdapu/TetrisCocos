#pragma once

#include "cocos2d.h"
#include "TetrisButton.h"
#include "Constants.h"

// Pause Scene for Local Multiplayer
class LocalPauseScene : public cocos2d::Scene
{
public:
	LocalPauseScene(MultiplayerGameMode gameMode) : gameMode(gameMode) {}
	static LocalPauseScene* create(std::string p1Score, std::string p2Score, MultiplayerGameMode gameMode);
	virtual bool init(std::string p1Score, std::string p2Score);

	void goBack(cocos2d::Ref * pSender);
	void rematch(cocos2d::Ref * pSender);
	void goToMainMenu(cocos2d::Ref * pSender);

private:
	TetrisButton * resumeBtn, *rematchBtn, *mainMenuBtn;
	void addButtons();
	MultiplayerGameMode gameMode;
};
