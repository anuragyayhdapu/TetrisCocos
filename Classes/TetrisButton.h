#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"
#include<functional>
#include <vector>

class TetrisButton : public cocos2d::Node
{
public:
	TetrisButton() : animating(false) {  }
	TetrisButton(std::function<void(cocos2d::Ref*)> _btnCallbackFunc, cocos2d::Color4F borderColor);
	virtual ~TetrisButton();

	static TetrisButton * TetrisButton::create(std::string text, cocos2d::Vec2 position, float size, cocos2d::Color4F borderColor = cocos2d::Color4F::ORANGE, FontAlign align = FontAlign::MIDDLE);
	static TetrisButton* create(std::function<void(cocos2d::Ref*)> _btnCallbackFunc, std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontAlign = FontAlign::LEFT, FontColorPattern = FontColorPattern::RANDOM_BLOCK, FontDrawPattern = FontDrawPattern::BORDERED, float btnWidth = 0);

	bool init(std::string text, cocos2d::Vec2 position, float size, FontColorPattern, FontDrawPattern, FontAlign, unsigned int width);

	void startAnimate();
	void stopAnimate();
	void reWrite(std::string text);
	bool nonInteractive;
	void drawBorder() { btnDrawNode->drawRect(leftPt, rightPt, cocos2d::Color4F::ORANGE); }
	void removeBorder() { btnDrawNode->clear(); }
	void freeze();

private:
	TetrisFont * font;
	cocos2d::Color4F borderColor;
	cocos2d::Vec2 leftPt;
	cocos2d::Vec2 rightPt;
	float width;
	cocos2d::DrawNode *btnDrawNode, *p, *s, **curr;	// primary and secondary fontDrawing nodes
	bool alreadyDrawn, alreadyClear;
	std::function<void(cocos2d::Ref*)> btnCallbackFunc;

	bool TetrisButton::insideBoundingBox(cocos2d::Vec2 pos);
	bool onMouseMove(cocos2d::EventMouse* _event);
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * _event);
	bool onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * _event);

	bool animating;
	void animate(float dt);

	std::vector<int>::iterator rIter;
	std::vector<int> randList;
	void createRandList();
};