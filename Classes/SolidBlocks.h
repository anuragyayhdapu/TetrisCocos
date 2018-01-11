#pragma once

#include "Constants.h"
#include "BoardPos.h"
#include "UnitBlock.h"
#include "Tetromino.h"
#include <unordered_map>
#include <forward_list>
#include <unordered_set>

class Tetromino;

class SolidBlocks : public cocos2d::Node {

private:
	std::list<Tetromino*> solidTetrominos;

	Tetromino* bucket[t_const::BUCKET_HEIGHT][t_const::BUCKET_WIDTH];

	// checks if a single row is filled
	bool rowFilled(int rowNum);
	
	// shift this tetromino down in bucket
	void shiftDown(Tetromino* tetromino);

	// create new tetromino for top blocks
	void divideTetromino(Tetromino * old, short y_axis);

public:
	// add new blocks in solidBlock
	void add(Tetromino* tetromino, bool firstTime = true);

	virtual bool init();
	CREATE_FUNC(SolidBlocks);

	bool find(BoardPos bPos) const;

	// shifts down hanging block to cover up the space
	void SolidBlocks::dropHangingBlocks();

	// clear filled rows
	int clearLines();

	const std::list<Tetromino*>& getSolidTetrominos() const { return solidTetrominos; }
};