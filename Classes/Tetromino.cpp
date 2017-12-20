#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}

bool Tetromino::init()
{
	if (!Node::init())
	{
		return false;
	}

	// initialze at spawn posiiton
	this->rotationState = Constant::SPAWN_ROTATION_STATE;
	this->gridMatrixPoint = Constant::SPAWN_POSITION;

	return true;
}
