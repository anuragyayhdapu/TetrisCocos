#pragma once

#include "BoardPos.h"
#include <vector>

// Rotation inspired from SRS-Simple Rotation System (http://tetris.wikia.com/wiki/SRS)

namespace TetrominoTemplate
{
	using xy = BoardPos;	// relative positions from grid top left corner
	using face = const std::vector<xy>;

	namespace L
	{
		face top = { xy(1,0), xy(1,1), xy(1,2), xy(2, 2) };
		face right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 2) };
		face bottom = { xy(0,0), xy(1,0), xy(1,1), xy(1, 2) };
		face left = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
	}

	namespace J
	{
		face top = { xy(1,0), xy(1,1), xy(1,2), xy(2, 2) };
		face right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 2) };
		face bottom = { xy(0,0), xy(1,0), xy(1,1), xy(1, 2) };
		face left = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
	}

	namespace T
	{
		face top = { xy(0,1), xy(1,1), xy(0,1), xy(2, 1) };
		face right = { xy(1,0), xy(1,1), xy(2,1), xy(1, 2) };
		face bottom = { xy(0,1), xy(1,1), xy(2,1), xy(1, 2) };
		face left = { xy(1,0), xy(1,1), xy(0,1), xy(1, 2) };
	}

	namespace I
	{
		face top = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
		face right = { xy(2,0), xy(2,1), xy(2,2), xy(2, 3) };
		face bottom = { xy(0,2), xy(1,2), xy(2,2), xy(3, 2) };
		face left = { xy(1,0), xy(1,1), xy(1,2), xy(1, 3) };
	}

	namespace S
	{
		face top = { xy(2,0), xy(1,0), xy(1,1), xy(0, 1) };
		face right = { xy(1,0), xy(1,1), xy(2,1), xy(2, 2) };
		face bottom = { xy(2,1), xy(1,1), xy(1,2), xy(0, 2) };
		face left = { xy(0,0), xy(0,1), xy(1,1), xy(1, 2) };
	}

	namespace Z
	{
		face top = { xy(0,0), xy(1,0), xy(1,1), xy(2, 1) };
		face right = { xy(2,0), xy(2,1), xy(1,1), xy(1, 2) };
		face bottom = { xy(0,1), xy(1,1), xy(1,2), xy(2, 2) };
		face left = { xy(0,2), xy(0,1), xy(1,1), xy(1, 0) };
	}

	namespace O
	{
		face top = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
		auto right = top;
		auto bottom = top;
		auto left = top;
	}
}