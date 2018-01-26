#pragma once

#include "cocos2d.h"

class TetrisFont : public cocos2d::Node
{
public:
	TetrisFont();
	virtual ~TetrisFont();
	static TetrisFont* create(std::string text, cocos2d::Color3B color, cocos2d::Vec2 position, short size);
	bool init(std::string text, cocos2d::Color3B color, cocos2d::Vec2 position, short size);

	void write(cocos2d::DrawNode* drawNode);

	static float u;	// text unit block size

private:
	std::string text;
	float size;	//this text size
	cocos2d::Color3B color;
	cocos2d::Vec2 midPt, leftPt, rightPt;

	void calcBoundingBoxPoints();
	void createFontBlocks();
};