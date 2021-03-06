#include "SolidBlocks.h"

SolidBlocks::SolidBlocks(short bucketLeft, short bucketRight, short bucketTop, short bucketBottom)
	:
	bucketLeft(bucketLeft),
	bucketRight(bucketRight),
	bucketTop(bucketTop),
	bucketBottom(bucketBottom)
{
}


SolidBlocks * SolidBlocks::create(short bucketLeft, short bucketRight, short bucketTop, short bucketBottom)
{
	SolidBlocks* block = new(std::nothrow)SolidBlocks(bucketLeft, bucketRight, bucketTop, bucketBottom);
	if (block && block->init())
	{
		block->autorelease();
	}
	else
	{
		delete block;
		block = nullptr;
	}
	return block;
}


bool SolidBlocks::init()
{
	if (!Node::init()) {
		return false;
	}

	// initialize bucket
	for (size_t i = 0; i < t_const::BUCKET_HEIGHT; i++)
		for (size_t j = 0; j < t_const::BUCKET_WIDTH; j++)
			bucket[i][j] = nullptr;

	return true;
}


bool SolidBlocks::rowFilled(int rowNum) {

	for (size_t i = 0; i < t_const::BUCKET_WIDTH; i++)
		if (bucket[rowNum][i] == nullptr)
			return false;

	return true;
}


void SolidBlocks::add(Tetromino* tetromino, bool firstTime)
{
	// change owenrship
	tetromino->retain();
	tetromino->removeFromParent();
	this->addChild(tetromino);
	tetromino->release();

	for (auto block : tetromino->getUnitBlocksVec())
	{
		// adjust block position relative to bucket
		auto relativeX = block->getX() - bucketLeft;
		auto relativeY = block->getY() - bucketTop;

		bucket[relativeY][relativeX] = tetromino;
	}

	if (firstTime)
	{
		solidTetrominos.push_front(tetromino);
	}
}


// shift this tetromino dow in bucket
void SolidBlocks::shiftDown(Tetromino* tetromino)
{
	// before moving : remove all blocks from bucket
	for (auto block : tetromino->getUnitBlocksVec())
	{
		// adjust block position relative to bucket
		auto relativeX = block->getX() - bucketLeft;
		auto relativeY = block->getY() - bucketTop;

		bucket[relativeY][relativeX] = nullptr;
	}

	// move down this tetromino
	while (tetromino->moveDown(*this))
		;

	// after moving : update new positions
	add(tetromino, false);
}


bool SolidBlocks::find(BoardPos bPos) const
{
	// adjust block position relative to bucket
	auto relativeX = bPos.x - bucketLeft;
	auto relativeY = bPos.y - bucketTop;

	return bucket[relativeY][relativeX] != nullptr;
}


void SolidBlocks::dropHangingBlocks()
{
	for (auto i = t_const::BUCKET_HEIGHT - 2; i >= 0; --i)
	{
		for (int j = 0; j < t_const::BUCKET_WIDTH; j++)
		{
			if (bucket[i][j] != nullptr)
			{
				// move this tetromino till it hits bottom or a solidblock
				auto tetromino = bucket[i][j];
				shiftDown(tetromino);
			}
		}
	}
}


int SolidBlocks::clearLines()
{
	int numRowsFilled = 0;

	// delete filled rows
	for (auto i = t_const::BUCKET_HEIGHT - 1; i >= 0; --i)
	{
		if (rowFilled(i))
		{
			++numRowsFilled;

			for (size_t j = 0; j < t_const::BUCKET_WIDTH; j++)
			{
				// calculate block position relative to bucket
				auto absoluteX = j + bucketLeft;
				auto absoluteY = i + bucketTop;
				bucket[i][j]->removeBlock(BoardPos(absoluteX, absoluteY));

				// check if tetromino is to be divided
				for (auto block : bucket[i][j]->getUnitBlocksVec())
				{
					// check for bottom blocks
					if (block->getY() > i)
					{
						divideTetromino(bucket[i][j], i);
						break;
					}
				}

				// if after removing this block tetromino becomes empty,
				// erase this tetromino
				if (bucket[i][j]->empty())
				{
					for (auto iter = solidTetrominos.begin(); iter != solidTetrominos.end(); ++iter)
					{
						if (*iter == bucket[i][j])
						{
							this->removeChild(*iter);
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


void SolidBlocks::divideTetromino(Tetromino* old, short y)
{
	bool createNewTetromino = false;
	std::forward_list<BoardPos> topBlockPos;

	// check for top blocks
	for (auto block : old->getUnitBlocksVec())
	{
		if (block->getY() < y)
		{
			createNewTetromino = true;
			topBlockPos.push_front(block->currPos());
		}
	}

	// create new Tetromino with top blocks
	if (createNewTetromino == true)
	{
		auto topTetromino = Tetromino::createWithBlocks(*old, topBlockPos);
		this->addChild(topTetromino);
		solidTetrominos.push_back(topTetromino);

		// update bucket
		for (auto pos : topBlockPos)
		{
			// adjust block position relative to bucket
			auto relativeX = pos.x - bucketLeft;
			auto relativeY = pos.y - bucketTop;
			bucket[relativeY][relativeX] = topTetromino;
		}
	}

	// update bottom tetromino
	for (auto pos : topBlockPos)
	{
		old->removeBlock(pos);
	}
}


void SolidBlocks::clear()
{
	// clear bucket
	for (size_t i = 0; i < t_const::BUCKET_HEIGHT; i++)
		for (size_t j = 0; j < t_const::BUCKET_WIDTH; j++)
			bucket[i][j] = nullptr;

	solidTetrominos.clear();

	this->removeAllChildren();
}