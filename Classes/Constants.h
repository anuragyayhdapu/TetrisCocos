#pragma once

#include "BoardPos.h"
#include <vector>

// constants accessed from multiple files
namespace t_const
{
	const int BUCKET_WIDTH = 10;
	const int BUCKET_HEIGHT = 23;
	const int BUCKET_TOP_GAP = 3;

	const int WINDOW_WIDTH = 5;
	const int WINDOW_HEIGHT = 12;

	const int NUM_OF_UNIT_BLOCKS_IN_TETROMINO = 4;

	// for cricket
	namespace cr
	{
		const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 30;
		const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 20;

		const int WINDOW_TOP = 0;
		const int WINDOW_LEFT = 0;
		const int WINDOW_HEIGHT = 28;
		const int WINDOW_RIGHT = WINDOW_LEFT + WINDOW_WIDTH;
		const int WINDOW_BOTTOM = WINDOW_TOP + WINDOW_HEIGHT;

		const int BUCKET_LEFT = NUM_OF_UNIT_BLOCKS_IN_WIDTH - BUCKET_WIDTH - 2;
		const int BUCKET_RIGHT = BUCKET_LEFT + BUCKET_WIDTH;
		const int BUCKET_TOP = 0;
		const int BUCKET_BOTTOM = BUCKET_TOP + BUCKET_HEIGHT;


		const BoardPos SPAWN_POSITION((BUCKET_LEFT + BUCKET_WIDTH / 2) - NUM_OF_UNIT_BLOCKS_IN_TETROMINO / 2, BUCKET_TOP);
	}

	// for local multiplayer
	namespace lm
	{
		const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 30;
		const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 12;

		const int BUCKET_LEFT = 1;
		const int BUCKET_RIGHT = BUCKET_LEFT + BUCKET_WIDTH;
		const int BUCKET_TOP = 0;
		const int BUCKET_BOTTOM = BUCKET_TOP + BUCKET_HEIGHT;

		const int WINDOW_TOP = 0;
		const int WINDOW_LEFT_GAP = 3;
		const int WINDOW_LEFT = BUCKET_RIGHT + WINDOW_LEFT_GAP;
		const int WINDOW_RIGHT = WINDOW_LEFT + WINDOW_WIDTH;
		const int WINDOW_BOTTOM = WINDOW_TOP + WINDOW_HEIGHT;

		const BoardPos SPAWN_POSITION((BUCKET_LEFT + BUCKET_WIDTH / 2) - NUM_OF_UNIT_BLOCKS_IN_TETROMINO / 2, BUCKET_TOP);
	}

	// for single player
	namespace sp
	{
		const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 25;
		const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 25;

		const int BUCKET_LEFT = 5;
		const int BUCKET_RIGHT = BUCKET_LEFT + BUCKET_WIDTH;
		const int BUCKET_TOP = 0;
		const int BUCKET_BOTTOM = BUCKET_TOP + BUCKET_HEIGHT;

		const int WINDOW_TOP = 0;
		const int WINDOW_LEFT_GAP = 3;
		const int WINDOW_LEFT = BUCKET_RIGHT + WINDOW_LEFT_GAP;
		const int WINDOW_RIGHT = WINDOW_LEFT + WINDOW_WIDTH;
		const int WINDOW_BOTTOM = WINDOW_TOP + WINDOW_HEIGHT;

		const BoardPos SPAWN_POSITION((BUCKET_LEFT + BUCKET_WIDTH / 2) - NUM_OF_UNIT_BLOCKS_IN_TETROMINO / 2, BUCKET_TOP);
	}

	const int ONE_LINE_CLEAR_SCORE = 10;
	const int LEVEL_CHANGE_LINE_CLEAR_COUNT = 5;
	const float START_SPEED = 1.0f;
	const float SPEED_DECREASE = 0.7f;

	const short WINDOW_SIZE = 3;
	const short GRID_MATRIX_SIZE = 4;

	const short FONT_WIDTH = 5;
	const short FONT_HEIGHT = 5;

	const float MEDIUM_DESIGN_RESOLUTION_HEIGHT = 768;
	const float POINT_SIZE = 1.0f;
}

enum TetrisEvent {
	INCREMENT_RAND_ITERATOR, GAMEOVER,
	LEVEL_UP, HIGH_SCORE_UP, SCORE_UP,
	MOVING_TET_MOVED, SOLIDBLOCKS_UPDATED
};

enum FontColorPattern {
	FULL, RANDOM_WORD, RANDOM_BLOCK
};

enum FontDrawPattern {
	SOLID, BORDERED
};

enum FontAlign {
	LEFT, MIDDLE, RIGHT
};

enum MultiplayerGameMode {
	LAST_MAN_STANDING	// no timer, no score, only level, survive till end
	, ALL_ABOUT_SCORE	// no timer, score, level, one with the highest score wins
	, RACE_AGAINS_TIME	// timer, score, level, make highest score in given time
};

enum CricketInnings {
	FIRST_INIINGS,
	SECOND_INNING
};


namespace t_network {

	enum Messagetype {
		GAME_OVER_SIGNAL = 0,	// send score data
		GAME_PAUSE_SIGNAL = 1,
		GAME_START_SIGNAL = 3,
		GAME_RESUME_SIGNAL = 4,

		ENTIRE_BOARD_STATE = 5,	// send moving tetromino & solidblocks draw data, score & level
		MOVING_TETROMINO_STATE = 6	// send moving tetromino draw data
	};

	const unsigned int SERVER_PORT = 60000;
	const short MAX_CONNECTIONS_ALLOWED = 2;
	const short MAX_INCOMING_CONNECTIONS_ALLOWED = 1;
}