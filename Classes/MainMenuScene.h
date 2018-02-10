#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"
#include "TetrisButton.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
	void GoToSinglePlayerScene(Ref * pSender);

private:
	TetrisButton *spStartBtn;
};
