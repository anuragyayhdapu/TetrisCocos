#pragma once

#include "cocos2d.h"
#include <forward_list>
#include "DrawData.h"
#include "Constants.h"

class TetrisFont : public cocos2d::Node
{
public:
	TetrisFont();
	virtual ~TetrisFont();
	static TetrisFont* create(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size,
		FontColorPattern, FontAlign align = FontAlign::LEFT);
	bool init(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, float size, 
		FontColorPattern, FontAlign);

	void write(cocos2d::DrawNode* drawNode);
	bool insideBoundingBox(cocos2d::Vec2 pos);

	static float u;	// text unit block size

private:
	std::string text;
	float size;	//this text size
	cocos2d::Color4F color;
	cocos2d::Vec2 leftPt, rightPt;
	std::forward_list<DrawData> fontBlocksDD;
	FontColorPattern colorPattern;

	void createFontBlocks();
};