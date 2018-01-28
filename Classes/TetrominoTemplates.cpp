#include "TetrominoTemplates.h"
#include "Constants.h"
#include <fstream>

// Rotation inspired from SRS-Simple Rotation System (http://tetris.wikia.com/wiki/SRS)

std::array<RotationQ*, TetrominoTemplate::size> * TetrominoTemplate::rotationTemplates = []() {

	using xy = BoardPos;
	using Face = const std::array<xy, 4>*;
	std::array<RotationQ*, size> * rotationTemplates = new std::array<RotationQ*, size>;

	// L
	Face l_top = new std::array<BoardPos, 4>{ xy(1, 0), xy(1, 1), xy(1, 2), xy(2, 2) };
	Face l_right = new std::array<BoardPos, 4>{ xy(2, 1), xy(1, 1), xy(0, 1), xy(0, 2) };
	Face l_bottom = new std::array<BoardPos, 4>{ xy(0, 0), xy(1, 0), xy(1, 1), xy(1, 2) };
	Face l_left = new std::array<BoardPos, 4>{ xy(0, 1), xy(1, 1), xy(2, 1), xy(2, 0) };
	rotationTemplates->at(0) = new RotationQ(l_top, l_right, l_bottom, l_left);

	// J
	Face j_top = new std::array<BoardPos, 4>{ xy(2, 0), xy(2, 1), xy(2, 2), xy(1, 2) };
	Face j_right = new std::array<BoardPos, 4>{ xy(3, 1), xy(2, 1), xy(1, 1), xy(1, 0) };
	Face j_bottom = new std::array<BoardPos, 4>{ xy(2, 2), xy(2, 1), xy(2, 0), xy(3, 0) };
	Face j_left = new std::array<BoardPos, 4>{ xy(3, 1), xy(3, 0), xy(2, 0), xy(1, 0) };
	rotationTemplates->at(1) = new RotationQ(j_top, j_right, j_bottom, j_left);

	// T
	Face t_top = new std::array<BoardPos, 4>{ xy(0, 1), xy(1, 1), xy(1, 0), xy(2, 1) };
	Face t_right = new std::array<BoardPos, 4>{ xy(1, 0), xy(1, 1), xy(2, 1), xy(1, 2) };
	Face t_bottom = new std::array<BoardPos, 4>{ xy(0, 1), xy(1, 1), xy(2, 1), xy(1, 2) };
	Face t_left = new std::array<BoardPos, 4>{ xy(1, 0), xy(1, 1), xy(0, 1), xy(1, 2) };
	rotationTemplates->at(2) = new RotationQ(t_top, t_right, t_bottom, t_left);

	// I
	Face i_top = new std::array<BoardPos, 4>{ xy(0, 1), xy(1, 1), xy(2, 1), xy(3, 1) };
	Face i_right = new std::array<BoardPos, 4>{ xy(2, 0), xy(2, 1), xy(2, 2), xy(2, 3) };
	Face i_bottom = new std::array<BoardPos, 4>{ xy(0, 2), xy(1, 2), xy(2, 2), xy(3, 2) };
	Face i_left = new std::array<BoardPos, 4>{ xy(1, 0), xy(1, 1), xy(1, 2), xy(1, 3) };
	rotationTemplates->at(3) = new RotationQ(i_top, i_right, i_bottom, i_left);

	// S
	Face s_top = new std::array<BoardPos, 4>{ xy(2, 0), xy(1, 0), xy(1, 1), xy(0, 1) };
	Face s_right = new std::array<BoardPos, 4>{ xy(1, 0), xy(1, 1), xy(2, 1), xy(2, 2) };
	Face s_bottom = new std::array<BoardPos, 4>{ xy(2, 1), xy(1, 1), xy(1, 2), xy(0, 2) };
	Face s_left = new std::array<BoardPos, 4>{ xy(0, 0), xy(0, 1), xy(1, 1), xy(1, 2) };
	rotationTemplates->at(4) = new RotationQ(s_top, s_right, s_bottom, s_left);

	// Z
	Face z_top = new std::array<BoardPos, 4>{ xy(0, 0), xy(1, 0), xy(1, 1), xy(2, 1) };
	Face z_right = new std::array<BoardPos, 4>{ xy(2, 0), xy(2, 1), xy(1, 1), xy(1, 2) };
	Face z_bottom = new std::array<BoardPos, 4>{ xy(0, 1), xy(1, 1), xy(1, 2), xy(2, 2) };
	Face z_left = new std::array<BoardPos, 4>{ xy(0, 2), xy(0, 1), xy(1, 1), xy(1, 0) };
	rotationTemplates->at(5) = new RotationQ(z_top, z_right, z_bottom, z_left);

	// O
	Face o_top = new std::array<BoardPos, 4>{ xy(1, 0), xy(2, 0), xy(1, 1), xy(2, 1) };
	Face o_right = new std::array<BoardPos, 4>{ xy(1, 0), xy(2, 0), xy(1, 1), xy(2, 1) };
	Face o_bottom = new std::array<BoardPos, 4>{ xy(1, 0), xy(2, 0), xy(1, 1), xy(2, 1) };
	Face o_left = new std::array<BoardPos, 4>{ xy(1, 0), xy(2, 0), xy(1, 1), xy(2, 1) };
	rotationTemplates->at(6) = new RotationQ(o_top, o_right, o_bottom, o_left);


	return rotationTemplates;

}();


std::array<cocos2d::Color4B, TetrominoTemplate::size>* TetrominoTemplate::colorTemplates = []() {

	std::array<cocos2d::Color4B, size> * colorTemplates = new std::array<cocos2d::Color4B, size>{
		cocos2d::Color4B(126, 153, 123, 255),	// L
			cocos2d::Color4B(70, 132, 153, 255),	// J
			cocos2d::Color4B(176, 94, 168, 255),	// T
			cocos2d::Color4B(0, 128, 128, 255),		// I
			cocos2d::Color4B(192, 57, 25, 255),		// Z
			cocos2d::Color4B(87, 153, 81, 255),		// S
			cocos2d::Color4B(204, 196, 114, 255)	// O
	};

	return colorTemplates;
}();


std::array<cocos2d::Color4B, TetrominoTemplate::size> * TetrominoTemplate::borderColorTemplates = []() {

	std::array<cocos2d::Color4B, size> * borderColorTemplates = new std::array<cocos2d::Color4B, size>{
		cocos2d::Color4B::BLACK,	// L
			cocos2d::Color4B::BLACK,	// J
			cocos2d::Color4B::BLACK,	// T
			cocos2d::Color4B::BLACK,	// I
			cocos2d::Color4B::BLACK,	// Z
			cocos2d::Color4B::BLACK,	// S
			cocos2d::Color4B::BLACK		// O
	};

	return borderColorTemplates;
}();


std::map<char, std::vector<std::string>> *
TetrominoTemplate::fontTemplates = []() {

	std::map<char, std::vector<std::string>> * fontTemplates = new std::map<char, std::vector<std::string>>();

	// open file tetrisFontTemplate
	std::ifstream fontFile;
	fontFile.open("../Resources/TetrisFontTemplate.txt");

	if (fontFile.is_open())
	{
		std::string line;

		while (std::getline(fontFile, line))
		{
			// read one character, that's key to the map
			char key = line.at(0);

			// read next five lines, and add to 2-d matrix
			std::vector<std::string> value;
			for (int i = 0; i < t_const::FONT_WIDTH; ++i)
			{
				getline(fontFile, line);
				value.push_back(line);
			}
			fontTemplates->insert(std::pair<char, std::vector<std::string>>(key, value));
		}
	}
	fontFile.close();

	return fontTemplates;
}();