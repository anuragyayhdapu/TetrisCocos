#pragma once

#include "Constants.h"
#include "BoardPos.h"
#include "UnitBlock.h"
#include "Tetromino.h"
#include <unordered_map>
#include <forward_list>
#include <unordered_set>

class SolidBlocks : public cocos2d::Node {

private:
	// unitBlocks hudled together
	struct SolidTetromino {
		std::unordered_map<BoardPos, UnitBlock*, BoardPosComparator> unitBlocks;	
		bool moved = false;
	};
	std::forward_list<SolidTetromino> solidTetrominos;

	UnitBlock * bucket[Constant::BUCKET_HEIGHT][Constant::BUCKET_WIDTH];

	// checks if a single row is filled
	bool rowFilled(int rowNum);

	// add new blocks in solidBlock
	void add(const std::vector<UnitBlock*>& newBlocks);

public:

	virtual bool init();
	CREATE_FUNC(SolidBlocks);

	bool find(BoardPos bPos) {
		return bucket[bPos.x][bPos.y] != nullptr;
	}

	// checks which rows are filled, deletes them, and shifts top rows down to cover up the space
	void updateSolidBlocks(Tetromino* movableTetromino);

	// draws / redraws solidBlocks
	void drawSolidBlocks(std::vector<int> rows = {});
};