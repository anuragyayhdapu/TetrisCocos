#include "TetrominoTemplates.h"
#include "Constants.h"

// Rotation inspired from SRS-Simple Rotation System (http://tetris.wikia.com/wiki/SRS)

std::vector<RotationQ> TetrominoTemplate::rotationTemplates = []() {

	using xy = BoardPos;
	using Face = const std::vector<xy>;
	std::vector<RotationQ> rotationTemplates(7);

	// L
	Face l_top = { xy(1,0), xy(1,1), xy(1,2), xy(2, 2) };
	Face l_right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 2) };
	Face l_bottom = { xy(0,0), xy(1,0), xy(1,1), xy(1, 2) };
	Face l_left = { xy(0,1), xy(1,1), xy(2,1), xy(2, 0) };
	RotationQ l_rotations(l_top, l_right, l_bottom, l_left);
	rotationTemplates.at(0) = l_rotations;

	// J
	Face j_top = { xy(1,0), xy(1,1), xy(1,2), xy(0, 2) };
	Face j_right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 0) };
	Face j_bottom = { xy(1,2), xy(1,1), xy(1,0), xy(2, 0) };
	Face j_left = { xy(2,1), xy(2,0), xy(1,0), xy(0, 0) };
	RotationQ j_rotations(j_top, j_right, j_bottom, j_left);
	rotationTemplates.at(1) = j_rotations;

	// T
	Face t_top = { xy(0,1), xy(1,1), xy(1,0), xy(2, 1) };
	Face t_right = { xy(1,0), xy(1,1), xy(2,1), xy(1, 2) };
	Face t_bottom = { xy(0,1), xy(1,1), xy(2,1), xy(1, 2) };
	Face t_left = { xy(1,0), xy(1,1), xy(0,1), xy(1, 2) };
	RotationQ t_rotations(t_top, t_right, t_bottom, t_left);
	rotationTemplates.at(2) = t_rotations;

	// I
	Face i_top = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
	Face i_right = { xy(2,0), xy(2,1), xy(2,2), xy(2, 3) };
	Face i_bottom = { xy(0,2), xy(1,2), xy(2,2), xy(3, 2) };
	Face i_left = { xy(1,0), xy(1,1), xy(1,2), xy(1, 3) };
	RotationQ i_rotations(i_top, i_right, i_bottom, i_left);
	rotationTemplates.at(3) = i_rotations;

	// S
	Face s_top = { xy(2,0), xy(1,0), xy(1,1), xy(0, 1) };
	Face s_right = { xy(1,0), xy(1,1), xy(2,1), xy(2, 2) };
	Face s_bottom = { xy(2,1), xy(1,1), xy(1,2), xy(0, 2) };
	Face s_left = { xy(0,0), xy(0,1), xy(1,1), xy(1, 2) };
	RotationQ s_rotations(s_top, s_right, s_bottom, s_left);
	rotationTemplates.at(4) = s_rotations;

	// Z
	Face z_top = { xy(0,0), xy(1,0), xy(1,1), xy(2, 1) };
	Face z_right = { xy(2,0), xy(2,1), xy(1,1), xy(1, 2) };
	Face z_bottom = { xy(0,1), xy(1,1), xy(1,2), xy(2, 2) };
	Face z_left = { xy(0,2), xy(0,1), xy(1,1), xy(1, 0) };
	RotationQ z_rotations(z_top, z_right, z_bottom, z_left);
	rotationTemplates.at(5) = z_rotations;

	// O
	Face o_top = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	Face o_right = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	Face o_bottom = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	Face o_left = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	RotationQ o_rotations(o_top, o_right, o_bottom, o_left);
	rotationTemplates.at(6) = o_rotations;


	return rotationTemplates;

}();


std::vector<cocos2d::Color4B> TetrominoTemplate::colorTemplates = []() {

	std::vector<cocos2d::Color4B> colorTemplates;

	// L
	colorTemplates.push_back(cocos2d::Color4B(126, 153, 123, 255));

	// J
	colorTemplates.push_back(cocos2d::Color4B(70, 132, 153, 255));

	// T
	colorTemplates.push_back(cocos2d::Color4B(176, 94, 168, 255));

	// I
	colorTemplates.push_back(cocos2d::Color4B(0, 128, 128, 255));

	// Z
	colorTemplates.push_back(cocos2d::Color4B(192, 57, 25, 255));

	// S
	colorTemplates.push_back(cocos2d::Color4B(87, 153, 81, 255));

	// O
	colorTemplates.push_back(cocos2d::Color4B(204, 196, 114, 255));

	return colorTemplates;
}();


std::vector<cocos2d::Color4B> TetrominoTemplate::borderColorTemplates = []() {

	std::vector<cocos2d::Color4B> borderColorTemplates;

	// L
	borderColorTemplates.push_back(cocos2d::Color4B(48, 60, 46, 255));

	// J
	borderColorTemplates.push_back(cocos2d::Color4B(17, 31, 36, 255));

	// T
	borderColorTemplates.push_back(cocos2d::Color4B(67, 33, 64, 255));

	// I
	borderColorTemplates.push_back(cocos2d::Color4B(0, 43, 43, 255));

	// Z
	borderColorTemplates.push_back(cocos2d::Color4B(72, 21, 9, 255));

	// S
	borderColorTemplates.push_back(cocos2d::Color4B(30, 53, 28, 255));

	// O
	borderColorTemplates.push_back(cocos2d::Color4B(84, 79, 30, 255));

	return colorTemplates;
}();