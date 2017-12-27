#pragma once

#include "BoardPos.h"

// constants accessed from multiple files
namespace Constant
{
	const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 30;
	const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 25;
	const int NUM_OF_UNIT_BLOCKS_IN_TETROMINO = 4;

	const BoardPos SPAWN_POSITION(10, 0);

	const short GRID_MATRIX_SIZE = 4;
}