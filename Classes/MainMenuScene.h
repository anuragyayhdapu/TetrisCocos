#pragma once

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    virtual bool init();

	void GoToTetrisBoardScene(Ref * pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};
