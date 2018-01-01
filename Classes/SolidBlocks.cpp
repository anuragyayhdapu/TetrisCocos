#include "SolidBlocks.h"


bool SolidBlocks::init()
{
	if (!Node::init()) {
		return false;
	}

	// initialize bucket
	for (size_t i = 0; i < Constant::BUCKET_HEIGHT; i++)
		for (size_t j = 0; j < Constant::BUCKET_WIDTH; j++)
			bucket[i][j] = nullptr;

	return true;
}


bool SolidBlocks::rowFilled(int rowNum) {

	for (size_t i = 0; i < Constant::BUCKET_WIDTH; i++)
		if (bucket[rowNum][i] == nullptr)
			return false;

	return true;
}


void SolidBlocks::add(const std::vector<UnitBlock*>& newBlocks) {
	// add to internal solidTetrominos also
	SolidTetromino st;

	for (auto newBlock : newBlocks)
	{
		auto solidBlock = UnitBlock::create(newBlock->getX(), newBlock->getY(), newBlock->getColor());
		bucket[solidBlock->getX()][solidBlock->getY()] = solidBlock;
		this->addChild(solidBlock);

		st.unitBlocks[solidBlock->currPos()] = solidBlock;
	}

	solidTetrominos.push_front(st);
}


void SolidBlocks::drawSolidBlocks(std::vector<int> rows)
{
	// draw entire matrix
	if (rows.size() == 0)
	{
		for (size_t i = 0; i < Constant::BUCKET_HEIGHT; i++)
		{
			for (size_t j = 0; j < Constant::BUCKET_WIDTH; j++)
			{
				if (bucket[i][j] != nullptr)
					bucket[i][j]->drawBlock();
			}
		}
	}

	// draw selected rows
	else
	{
		for each (auto i in rows)
		{
			for (size_t j = 0; j < Constant::BUCKET_WIDTH; j++)
			{
				if (bucket[i][j] != nullptr)
					bucket[i][j]->drawBlock();
			}
		}
	}
}


void SolidBlocks::updateSolidBlocks(Tetromino * movableTetromino)
{
	// adds all blocks of this tetromino in solidblocks matrix
	add(movableTetromino->getUnitBlocksVec());

	// check if any rows are filled
	std::unordered_set<int> filledRows;
	for each (auto block in movableTetromino->getUnitBlocksVec())
	{
		auto y = block->getY();
		if (rowFilled(y) == true)
			filledRows.insert(y);
	}

	// delete thows rows
	for each (auto i in filledRows)
	{
		for (size_t j = 0; j < Constant::BUCKET_WIDTH; j++)
		{
			// clear drawNodes
			bucket[i][j]->clearDrawnBlock();


			// find solidTetromino for this unitBlock
			for (auto &iterSt = solidTetrominos.begin(); iterSt != solidTetrominos.end(); iterSt++)
			{
				auto &iterBlock = iterSt->unitBlocks.find(BoardPos(i, j));
				if (iterBlock != iterSt->unitBlocks.end())
				{
					iterBlock->second = nullptr;	// dereference Node count
					iterSt->unitBlocks.erase(iterBlock);

					// if after removing this block tetromino becomes empty,
					// erase this tetromino
					if (iterSt->unitBlocks.empty())
					{
						solidTetrominos.erase_after(iterSt);
					}
				}
			}

			// set nullptr in matrix
			bucket[i][j] = nullptr;
		}
	}

	// shift above rows down

	// get lowest x from filled rows
	int lowX = Constant::BUCKET_HEIGHT;
	for each (auto x in filledRows)
	{
		if (x < lowX)
			lowX = x;
	}

	// move all tetromino of the lowest row, repeat recursively till top
	for (int i = lowX + 1; i >= 0; i--)
	{
		for (int j = 0; j < Constant::BUCKET_WIDTH; j++)
		{
			//	TODO: find this u* in st*
			// TODO: move that st* and update in matrix
			// TODO: repeat for entire row
		}
	}

}