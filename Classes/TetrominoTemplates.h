#pragma once

#include "BoardPos.h"
#include "RotationQ.h"
#include <array>
#include "cocos2d.h"
#include <list>


class TetrominoTemplate
{
public:
	const static short size = 7;
	static std::array<RotationQ*, size> * rotationTemplates;
	static std::array<cocos2d::Color4B, size> * colorTemplates;
	static std::array<cocos2d::Color4B, size> * borderColorTemplates;
	static std::map<char, std::vector<std::string>> * fontTemplates;
};	