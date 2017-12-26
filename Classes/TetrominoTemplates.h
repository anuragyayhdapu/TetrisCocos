#pragma once

#include "BoardPos.h"
#include <vector>

// Rotation inspired from SRS-Simple Rotation System (http://tetris.wikia.com/wiki/SRS)

namespace TetrominoTemplate
{
	using xy = BoardPos;	// relative positions from grid top left corner
	using Face = const std::vector<xy>;

	namespace L
	{
		extern Face top, right, bottom, left;
	}

	namespace J
	{
		extern Face top, right, bottom, left;
	}

	namespace T
	{
		extern Face top, right, bottom, left;
	}

	namespace I
	{
		extern Face top, right, bottom, left;
	}

	namespace S
	{
		extern Face top, right, bottom, left;
	}

	namespace Z
	{
		extern Face top, right, bottom, left;
	}

	namespace O
	{
		extern Face top, right, bottom, left;
	}
}