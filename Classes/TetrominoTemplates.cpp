#include "TetrominoTemplates.h"
#include "Constants.h"

// Rotation inspired from SRS-Simple Rotation System (http://tetris.wikia.com/wiki/SRS)

std::vector<RotationQ> TetrominoTemplate::rotationTemplates = []() {

	using xy = BoardPos;
	using Face = const std::vector<xy>;
	std::vector<RotationQ> rotationTemplates;

	// L
	Face l_top = { xy(1,0), xy(1,1), xy(1,2), xy(2, 2) };
	Face l_right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 2) };
	Face l_bottom = { xy(0,0), xy(1,0), xy(1,1), xy(1, 2) };
	Face l_left = { xy(0,1), xy(1,1), xy(2,1), xy(2, 0) };
	RotationQ l_rotations(l_top, l_right, l_bottom, l_left);
	rotationTemplates.push_back(l_rotations);

	// J
	Face j_top = { xy(1,0), xy(1,1), xy(1,2), xy(0, 2) };
	Face j_right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 0) };
	Face j_bottom = { xy(1,2), xy(1,1), xy(1,0), xy(2, 0) };
	Face j_left = { xy(2,1), xy(2,0), xy(1,0), xy(0, 0) };
	RotationQ j_rotations(j_top, j_right, j_bottom, j_left);
	rotationTemplates.push_back(j_rotations);

	// T
	Face t_top = { xy(0,1), xy(1,1), xy(1,0), xy(2, 1) };
	Face t_right = { xy(1,0), xy(1,1), xy(2,1), xy(1, 2) };
	Face t_bottom = { xy(0,1), xy(1,1), xy(2,1), xy(1, 2) };
	Face t_left = { xy(1,0), xy(1,1), xy(0,1), xy(1, 2) };
	RotationQ t_rotations(t_top, t_right, t_bottom, t_left);
	rotationTemplates.push_back(t_rotations);

	// I
	Face i_top = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
	Face i_right = { xy(2,0), xy(2,1), xy(2,2), xy(2, 3) };
	Face i_bottom = { xy(0,2), xy(1,2), xy(2,2), xy(3, 2) };
	Face i_left = { xy(1,0), xy(1,1), xy(1,2), xy(1, 3) };
	RotationQ i_rotations(i_top, i_right, i_bottom, i_left);
	rotationTemplates.push_back(i_rotations);

	// S
	Face s_top = { xy(2,0), xy(1,0), xy(1,1), xy(0, 1) };
	Face s_right = { xy(1,0), xy(1,1), xy(2,1), xy(2, 2) };
	Face s_bottom = { xy(2,1), xy(1,1), xy(1,2), xy(0, 2) };
	Face s_left = { xy(0,0), xy(0,1), xy(1,1), xy(1, 2) };
	RotationQ s_rotations(s_top, s_right, s_bottom, s_left);
	rotationTemplates.push_back(s_rotations);

	// Z
	Face z_top = { xy(0,0), xy(1,0), xy(1,1), xy(2, 1) };
	Face z_right = { xy(2,0), xy(2,1), xy(1,1), xy(1, 2) };
	Face z_bottom = { xy(0,1), xy(1,1), xy(1,2), xy(2, 2) };
	Face z_left = { xy(0,2), xy(0,1), xy(1,1), xy(1, 0) };
	RotationQ z_rotations(z_top, z_right, z_bottom, z_left);
	rotationTemplates.push_back(z_rotations);

	// O
	Face o_top = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	Face o_right = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	Face o_bottom = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	Face o_left = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	RotationQ o_rotations(o_top, o_right, o_bottom, o_left);
	rotationTemplates.push_back(o_rotations);


	return rotationTemplates;

}();