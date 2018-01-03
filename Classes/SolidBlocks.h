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

	Tetromino* bucket[Constant::BUCKET_HEIGHT][Constant::BUCKET_WIDTH];

	// checks if a single row is filled
	bool rowFilled(int rowNum);
	
	// shift this tetromino dow in bucket
	void shiftDown(Tetromino* tetromino);

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

	// draw entire matrix
	void drawSolidBlocks();
};