#pragma once

#include "cocos2d.h"
#include "TetrisButton.h"

class GameOverScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameOverScene);
	virtual bool init();

	void retry(cocos2d::Ref *pSender);
	void goToMainMenu(cocos2d::Ref *pSender);
	void quit(cocos2d::Ref *pSender);

private:
	TetrisButton *retryBtn, *mainMenuBtn, *quitBtn;
};
