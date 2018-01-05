#pragma once

#include "BoardPos.h"
#include "RotationQ.h"
#include <vector>
#include "cocos2d.h"


class TetrominoTemplate
{
public:
	const static int size = 7;
	static std::vector<RotationQ> rotationTemplates;
	static std::vector<cocos2d::Color4B> colorTemplates;
	static std::vector<cocos2d::Color4B> borderColorTemplates;
};