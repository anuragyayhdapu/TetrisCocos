#pragma once

#include "cocos2d.h"
#include "TetrisButton.h"

class PauseScene : public cocos2d::Scene
{
public:
	virtual bool init();
	CREATE_FUNC(PauseScene);
	void resume(cocos2d::Ref * pSender);
	void retry(cocos2d::Ref *pSender);
	void goToMainMenu(cocos2d::Ref * pSender);
	void quit(cocos2d::Ref * pSender);

private:
	TetrisButton *resumeBtn, *retryBtn, *mainMenuBtn, *quitBtn;
};
