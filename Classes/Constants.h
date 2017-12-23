#pragma once

#include "BoardPos.h"
#include <array>

// constants accessed from multiple files
namespace Constant
{
	const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 30;
	const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 25;

	enum RotationState
	{
		TOP, RIGHT, BOTTOM, LEFT
	};

	const BoardPos SPAWN_POSITION(15, 0);
	const RotationState SPAWN_ROTATION_STATE = TOP;

	const std::map<RotationState, RotationState> rightRotate = {
		{TOP, RIGHT}, {RIGHT, BOTTOM}, {BOTTOM, LEFT}, {LEFT, TOP} };

	const std::map<RotationState, RotationState> leftRotate = {
		{ TOP, LEFT },{ RIGHT, TOP },{ BOTTOM, RIGHT },{ LEFT, TOP } };

	const short GRID_MATRIX_SIZE = 4;
	using Row = std::array<bool, GRID_MATRIX_SIZE>;
	using Matrix = std::array<Row, GRID_MATRIX_SIZE>;
}