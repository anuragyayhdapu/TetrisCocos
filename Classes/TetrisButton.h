#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"
#include<functional>

class TetrisButton : public cocos2d::Node
{
public:
	TetrisButton() {  }
	TetrisButton(std::function<void(cocos2d::Ref*)> _btnCallbackFunc, cocos2d::Color4F borderColor);
	virtual ~TetrisButton();

	static TetrisButton* create(std::function<void(cocos2d::Ref*)> _btnCallbackFunc, std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontAlign = FontAlign::LEFT, FontColorPattern = FontColorPattern::RANDOM_BLOCK, FontDrawPattern = FontDrawPattern::BORDERED, float btnWidth = 0);

	bool init(std::string text, cocos2d::Vec2 position, float size, FontColorPattern, FontDrawPattern, FontAlign, unsigned int width);

	void startAnimate();
	void stopAnimate();

private:
	TetrisFont * font;
	cocos2d::Color4F borderColor;
	cocos2d::Vec2 leftPt;
	cocos2d::Vec2 rightPt;
	float width;
	cocos2d::DrawNode *btnDrawNode, *fontDrawNode;
	bool alreadyDrawn, alreadyClear;
	std::function<void(cocos2d::Ref*)> btnCallbackFunc;

	bool TetrisButton::insideBoundingBox(cocos2d::Vec2 pos);
	bool onMouseMove(cocos2d::EventMouse* _event);
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * _event);
	bool onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * _event);

	void animate(float dt);
};