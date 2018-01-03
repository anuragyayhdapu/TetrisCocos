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


void SolidBlocks::add(Tetromino* tetromino, bool firstTime)
{

	for (auto block : tetromino->getUnitBlocksVec())
	{
		// adjust block position relative to bucket
		auto relativeX = block->getX() - Constant::BUCKET_LEFT;
		auto relativeY = block->getY() - Constant::BUCKET_TOP;

		bucket[relativeY][relativeX] = tetromino;
	}

	if (firstTime)
		solidTetrominos.push_front(tetromino);
}


// shift this tetromino dow in bucket
void SolidBlocks::shiftDown(Tetromino* tetromino)
{
	// before moving : remove all blocks from bucket
	for (auto block : tetromino->getUnitBlocksVec())
	{
		// adjust block position relative to bucket
		auto relativeX = block->getX() - Constant::BUCKET_LEFT;
		auto relativeY = block->getY() - Constant::BUCKET_TOP;

		bucket[relativeY][relativeX] = nullptr;
	}

	// move down this tetromino
	while (tetromino->moveDown(*this))
		;

	// after moving : update new positions
	add(tetromino, false);
}


// draw entire matrix
void SolidBlocks::drawSolidBlocks()
{
	for (auto tetromino : solidTetrominos)
	{
		tetromino->drawTetromino();
	}
}


bool SolidBlocks::find(BoardPos bPos) const
{
	// adjust block position relative to bucket
	auto relativeX = bPos.x - Constant::BUCKET_LEFT;
	auto relativeY = bPos.y - Constant::BUCKET_TOP;

	return bucket[relativeY][relativeX] != nullptr;
}


void SolidBlocks::dropHangingBlocks()
{
	for (auto tetromino : solidTetrominos)
	{
		if (tetromino->checkMoveDown(*this))
		{
			shiftDown(tetromino);
		}
	}


	//for (auto i = Constant::BUCKET_HEIGHT; i >= 0; --i)
	//{
	//	for (int j = 0; j < Constant::BUCKET_WIDTH; j++)
	//	{
	//		if (bucket[i][j] != nullptr)
	//		{
	//			// move this tetromino till it hits bottom or a solidblock
	//			auto tetromino = bucket[i][j];
	//			shiftDown(tetromino);
	//		}
	//	}
	//}
}

int SolidBlocks::clearLines()
{
	int numRowsFilled = 0;

	// delete filled rows
	for (auto i = Constant::BUCKET_HEIGHT; i >= 0; --i)
	{
		if (rowFilled(i))
		{
			++numRowsFilled;

			for (size_t j = 0; j < Constant::BUCKET_WIDTH; j++)
			{
				// calculate block position relative to bucket
				auto absoluteX = j + Constant::BUCKET_LEFT;
				auto absoluteY = i + Constant::BUCKET_TOP;
				bucket[i][j]->removeBlock(BoardPos(absoluteX, absoluteY));

				// if after removing this block tetromino becomes empty,
				// erase this tetromino
				if (bucket[i][j]->empty())
				{
					for (auto iter = solidTetrominos.begin(); iter != solidTetrominos.end(); ++iter)
					{
						if (*iter == bucket[i][j])
						{
							solidTetrominos.erase(iter);
							break;
						}
					}
				}

				// set nullptr in matrix
				bucket[i][j] = nullptr;
			}
		}
	}


	return numRowsFilled;
}
