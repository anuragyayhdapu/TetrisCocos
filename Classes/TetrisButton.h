#pragma once

#include "cocos2d.h"
#include "TetrisFont.h"

class TetrisButton : public cocos2d::Node
{
public:
	TetrisButton(cocos2d::Color4F borderColor);
	virtual ~TetrisButton();

	static TetrisButton* create(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontAlign = FontAlign::LEFT, FontColorPattern = FontColorPattern::RANDOM_BLOCK, FontDrawPattern = FontDrawPattern::BORDERED, float btnWidth = 0);

	bool init(std::string text, cocos2d::Vec2 position, float size, FontColorPattern, FontDrawPattern, FontAlign, unsigned int width);

	bool TetrisButton::insideBoundingBox(cocos2d::Vec2 pos);


private:
	TetrisFont * font;
	cocos2d::Color4F borderColor;
	cocos2d::Vec2 leftPt;
	cocos2d::Vec2 rightPt;
	float width;

	cocos2d::DrawNode *btnDrawNode, *fontDrawNode;
};