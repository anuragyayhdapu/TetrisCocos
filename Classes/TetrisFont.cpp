#include "TetrisFont.h"
#include "Constants.h"
#include "TetrominoTemplates.h"


TetrisFont::TetrisFont()
{
}

TetrisFont::~TetrisFont()
{
}

float TetrisFont::u;

TetrisFont * TetrisFont::create(std::string text, cocos2d::Color3B color, cocos2d::Vec2 position, short size)
{
	TetrisFont* ptr = new(std::nothrow)TetrisFont();
	if (ptr && ptr->init(text, color, position, size))
	{
		ptr->autorelease();
	}
	else
	{
		delete ptr;
		ptr = nullptr;
	}
	return ptr;
}


bool TetrisFont::init(std::string text, cocos2d::Color3B color, cocos2d::Vec2 position, short size)
{
	if (!Node::init())
	{
		return false;
	}

	this->text = text;
	this->size = u * size;
	this->color = color;
	//midPt = position;
	leftPt = position;
	//calcBoundingBoxPoints();
	createFontBlocks();

	return true;
}


//void TetrisFont::calcBoundingBoxPoints()
//{
//	// top left
//	leftPt.x = midPt.x - ((text.length() / 2) * size);
//	leftPt.y = midPt.y;
//
//	// bottom right // watchout for magic numbers
//	rightPt.x = midPt.x + ((text.length() / 2) * size);
//	rightPt.y = midPt.y - (t_const::FONT_HEIGHT * size);
//
//	// adjust midPoint
//	//midPt.y -= (3 * size);
//}

void TetrisFont::createFontBlocks()
{
	cocos2d::Vec2 charLeftPt = leftPt;

	for (int k = 0; k < text.length(); ++k)
	{
		auto c = text.at(k);
		auto font = TetrominoTemplate::fontTemplates->at(c);

		

		// for spacing between words
		if (c == ' ')
		{
			charLeftPt.x += (2 * size);
			continue;
		}

		for (int i = 0; i < t_const::FONT_HEIGHT; ++i)
		{
			for (int j = 0; j < t_const::FONT_WIDTH; ++j)
			{
				if (font.at(i).at(j) == '1')
				{
					cocos2d::Vec2 blockLeftPt;
					blockLeftPt.x = charLeftPt.x + (j * size);
					blockLeftPt.y = charLeftPt.y - (i * size);

					// create a drawing data obj
					DrawData dd;
					cocos2d::Vec2 origin(blockLeftPt);
					cocos2d::Vec2 destination(origin.x + size, origin.y - size);
					cocos2d::Vec2 midPoint(origin.x + size / 2, origin.y - size / 2);
					dd.origin = origin;
					dd.destination = destination;
					dd.midPoint = midPoint;
					dd.color = cocos2d::Color4F(this->color);
					dd.borderColor = cocos2d::Color4F::BLACK;

					fontBlocksDD.push_front(dd);
				}
			}
		}

		charLeftPt.x += size * (t_const::FONT_WIDTH + 1);
	}
}


void TetrisFont::write(cocos2d::DrawNode * drawNode)
{
	for (auto dd : fontBlocksDD)
	{
		drawNode->drawSolidRect(dd.origin, dd.destination, dd.color);
		drawNode->drawRect(dd.origin, dd.destination, dd.borderColor);
	}
}