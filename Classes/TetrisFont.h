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
	static TetrisFont* create(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, short size, FontColorPattern pattern);
	bool init(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, short size, FontColorPattern pattern);

	void write(cocos2d::DrawNode* drawNode);

	static float u;	// text unit block size

private:
	std::string text;
	float size;	//this text size
	cocos2d::Color4F color;
	cocos2d::Vec2 /*midPt, */leftPt/*, rightPt*/;
	std::forward_list<DrawData> fontBlocksDD;
	FontColorPattern colorPattern;

	//void calcBoundingBoxPoints();
	void createFontBlocks();
};