#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"
#include "TetrisButton.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
	void GoToTetrisBoardScene(Ref * pSender);

private:
	TetrisButton *startBtn;
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * _event);
};
