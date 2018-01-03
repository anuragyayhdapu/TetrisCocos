#pragma once

#include "BoardPos.h"

// constants accessed from multiple files
namespace Constant
{
	const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 25;
	const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 25;
	const int NUM_OF_UNIT_BLOCKS_IN_TETROMINO = 4;

	const int BUCKET_WIDTH = 10;
	const int BUCKET_HEIGHT = 23;
	const int BUCKET_LEFT = 5;
	const int BUCKET_RIGHT = 5 + 10;
	const int BUCKET_TOP = 0;
	const int BUCKET_TOP_GAP = 3;
	const int BUCKET_BOTTOM = 0 + 23;


	const BoardPos SPAWN_POSITION(10, 0);

	const short GRID_MATRIX_SIZE = 4;
}