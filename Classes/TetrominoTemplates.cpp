#include "TetrominoTemplates.h"


namespace TetrominoTemplate
{
	namespace L
	{
		Face top = { xy(1,0), xy(1,1), xy(1,2), xy(2, 2) };
		Face right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 2) };
		Face bottom = { xy(0,0), xy(1,0), xy(1,1), xy(1, 2) };
		Face left = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
	}

	namespace J
	{
		Face top = { xy(1,0), xy(1,1), xy(1,2), xy(2, 2) };
		Face right = { xy(2,1), xy(1,1), xy(0,1), xy(0, 2) };
		Face bottom = { xy(0,0), xy(1,0), xy(1,1), xy(1, 2) };
		Face left = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
	}

	namespace T
	{
		Face top = { xy(0,1), xy(1,1), xy(0,1), xy(2, 1) };
		Face right = { xy(1,0), xy(1,1), xy(2,1), xy(1, 2) };
		Face bottom = { xy(0,1), xy(1,1), xy(2,1), xy(1, 2) };
		Face left = { xy(1,0), xy(1,1), xy(0,1), xy(1, 2) };
	}

	namespace I
	{
		Face top = { xy(0,1), xy(1,1), xy(2,1), xy(3, 1) };
		Face right = { xy(2,0), xy(2,1), xy(2,2), xy(2, 3) };
		Face bottom = { xy(0,2), xy(1,2), xy(2,2), xy(3, 2) };
		Face left = { xy(1,0), xy(1,1), xy(1,2), xy(1, 3) };
	}

	namespace S
	{
		Face top = { xy(2,0), xy(1,0), xy(1,1), xy(0, 1) };
		Face right = { xy(1,0), xy(1,1), xy(2,1), xy(2, 2) };
		Face bottom = { xy(2,1), xy(1,1), xy(1,2), xy(0, 2) };
		Face left = { xy(0,0), xy(0,1), xy(1,1), xy(1, 2) };
	}

	namespace Z
	{
		Face top = { xy(0,0), xy(1,0), xy(1,1), xy(2, 1) };
		Face right = { xy(2,0), xy(2,1), xy(1,1), xy(1, 2) };
		Face bottom = { xy(0,1), xy(1,1), xy(1,2), xy(2, 2) };
		Face left = { xy(0,2), xy(0,1), xy(1,1), xy(1, 0) };
	}

	namespace O
	{
		Face top = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
		Face right = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
		Face bottom = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
		Face left = { xy(1,0), xy(2,0), xy(1,1), xy(2, 1) };
	}
}