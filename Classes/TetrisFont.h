#pragma once

#include "cocos2d.h"
#include <forward_list>
#include "DrawData.h"
#include "Constants.h"

class TetrisFont : public cocos2d::Node
{
public:
	TetrisFont(std::string text, cocos2d::Color4F color, float size, FontColorPattern colorPattern, FontDrawPattern drawPattern, FontAlign align, cocos2d::Vec2 leftPt = cocos2d::Vec2(), cocos2d::Vec2 rightPt = cocos2d::Vec2());
	virtual ~TetrisFont();
	
	static TetrisFont* create(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontColorPattern, FontDrawPattern = FontDrawPattern::BORDERED, FontAlign align = FontAlign::LEFT);

	bool init(cocos2d::Vec2 position);

	void write(cocos2d::DrawNode* drawNode);
	void reWrite(std::string newText, cocos2d::DrawNode* drawNode);

	static float u;	// text unit block size

	cocos2d::Vec2 getLeftPt() { return leftPt; }
	cocos2d::Vec2 getRightPt() { return rightPt; }

private:
	std::string text;
	float size;	//this text size
	cocos2d::Color4F color;
	cocos2d::Vec2 leftPt, rightPt;
	std::forward_list<DrawData> fontBlocksDD;
	FontColorPattern colorPattern;
	FontDrawPattern drawPattern;
	FontAlign align;

	void createFontBlocks();
	void setBoundingPoints(cocos2d::Vec2 position);
};