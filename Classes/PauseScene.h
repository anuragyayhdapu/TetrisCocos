#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"

class PauseScene : public cocos2d::Scene
{
public:
	virtual bool init();
	CREATE_FUNC(PauseScene);
	void Resume(cocos2d::Ref * pSender);
	void GoToMainMenuScene(cocos2d::Ref * pSender);
	void Retry(cocos2d::Ref * pSender);

private:
	TetrisFont *resumeBtn, *retryBtn, *quitBtn;
};
