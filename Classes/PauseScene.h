#pragma once

#include "cocos2d.h"
#include "TetrisButton.h"

class PauseScene : public cocos2d::Scene
{
public:
	virtual bool init();
	CREATE_FUNC(PauseScene);

	static PauseScene* create(std::string score, std::string highScore, std::string lvl);
	virtual bool init(std::string score, std::string highScore, std::string lvl);

	void resume(cocos2d::Ref * pSender);
	void retry(cocos2d::Ref *pSender);
	void goToMainMenu(cocos2d::Ref * pSender);

private:
	TetrisButton *resumeBtn, *retryBtn, *mainMenuBtn;
	void addButtons();
};
