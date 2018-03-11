#pragma once

#include "cocos2d.h"
#include "TetrisButton.h"

class GameOverScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(GameOverScene);
	virtual bool init();

	static GameOverScene* create(std::string score, std::string highScore, std::string lvl);
	virtual bool init(std::string score, std::string highScore, std::string lvl);

	void retry(cocos2d::Ref *pSender);
	void goToMainMenu(cocos2d::Ref *pSender);
	void quit(cocos2d::Ref *pSender);

private:
	TetrisButton *retryBtn, *mainMenuBtn, *quitBtn;
	cocos2d::DrawNode *txtDrawNode;
	void drawButtons();
};
