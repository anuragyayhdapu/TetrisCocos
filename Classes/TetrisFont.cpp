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

TetrisFont * TetrisFont::create(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, short size, FontColorPattern pattern)
{
	TetrisFont* ptr = new(std::nothrow)TetrisFont();
	if (ptr && ptr->init(text, color, position, size, pattern))
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


bool TetrisFont::init(std::string text, cocos2d::Color4F color, cocos2d::Vec2 position, short size, FontColorPattern pattern)
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
	this->colorPattern = pattern;

	srand(time(NULL));
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
		if (colorPattern == FontColorPattern::RANDOM_WORD)
		{
			this->color = cocos2d::Color4F(TetrominoTemplate::colorTemplates->at(rand() % TetrominoTemplate::size));
		}

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
					if (colorPattern == FontColorPattern::RANDOM_BLOCK)
					{
						this->color = cocos2d::Color4F(TetrominoTemplate::colorTemplates->at(rand() % TetrominoTemplate::size));
					}

					cocos2d::Vec2 blockLeftPt;
					blockLeftPt.x = charLeftPt.x + (j * size);
					blockLeftPt.y = charLeftPt.y - (i * size);

					// create a drawing data obj
					DrawData dd;
					dd.origin = cocos2d::Vec2(blockLeftPt);
					dd.destination = cocos2d::Vec2(dd.origin.x + size, dd.origin.y - size);
					dd.midPoint = cocos2d::Vec2(dd.origin.x + size / 2, dd.origin.y - size / 2);
					dd.color = this->color;
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
		//drawNode->drawRect(dd.origin, dd.destination, dd.borderColor);
	}
}