#pragma once

#include "cocos2d.h"
#include <vector>
#include "DrawData.h"
#include "Constants.h"

class TetrisFont : public cocos2d::Node
{
public:
	TetrisFont(std::string text, cocos2d::Color4F color, float size, FontColorPattern colorPattern, FontDrawPattern drawPattern, FontAlign align, cocos2d::Vec2 position);
	virtual ~TetrisFont();
	
	static TetrisFont* create(std::string text, cocos2d::DrawNode* drawNode, cocos2d::Color4F color, cocos2d::Vec2 position, float size, FontColorPattern, FontDrawPattern = FontDrawPattern::BORDERED, FontAlign align = FontAlign::LEFT);

	bool init(cocos2d::DrawNode* drawNode);

	void reWrite(int newText, cocos2d::DrawNode* drawNode);
	void reWrite(std::string newText, cocos2d::DrawNode* drawNode);
	void reDraw(cocos2d::DrawNode* drawNode, cocos2d::Vec2 newPos);
	void reDraw(cocos2d::DrawNode* drawNode, cocos2d::Vec2 newPos, cocos2d::Color4F newColor);
	void drawBlock(cocos2d::DrawNode* drawNode, size_t index, cocos2d::Color4F color);

	static float u;	// text unit block size

	cocos2d::Vec2 getPos() { return position; }
	cocos2d::Vec2 getLeftPt() { return leftPt; }
	cocos2d::Vec2 getRightPt() { return rightPt; }
	std::string getText() { return text; }
	std::vector<DrawData> fontBlocksDD;

private:
	std::string text;
	float size;	//this text size
	cocos2d::Color4F color;
	cocos2d::Vec2 leftPt, rightPt, position;
	FontColorPattern colorPattern;
	FontDrawPattern drawPattern;
	FontAlign align;

	void write(cocos2d::DrawNode* drawNode);
	void createFontBlocks();
	void setBoundingPoints();
};