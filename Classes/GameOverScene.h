#pragma once

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void GoToTetrisBoardScene(cocos2d::Ref * pSender);

	void GoToMainMenuScene(cocos2d::Ref * pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};
