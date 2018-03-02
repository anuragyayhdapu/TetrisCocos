#include "Board.h"

USING_NS_CC;

Board::Board(std::list<short>::iterator& iter, short bucketLeft, short bucketRight, short bucketTop, short bucketBottom, BoardPos spawnPoint) :
	randListIter(iter),
	moveDelaySeconds(t_const::START_SPEED),
	tempDt(0.0f),
	bucketLeft(bucketLeft),
	bucketRight(bucketRight),
	bucketTop(bucketTop),
	bucketBottom(bucketBottom),
	spawnPoint(spawnPoint)
{
}

Board::~Board()
{
}

Board * Board::createBoard(double u, Vec2 leftTopPoint, std::list<short>::iterator& randListIter, unsigned int highScore, int level, short bucketLeft, short bucketRight, short bucketTop, short bucketBottom, BoardPos spawnpoint)
{
	Board* board = new(std::nothrow)Board(randListIter, bucketLeft, bucketRight, bucketTop, bucketBottom, spawnpoint);
	if (board && board->init(u, leftTopPoint, randListIter, highScore, level))
	{
		board->autorelease();
		return board;
	}
	else
	{
		delete board;
		board = nullptr;
		return nullptr;
	}
}

bool Board::init(double u, Vec2 leftTopPoint, std::list<short>::iterator& randListIter, unsigned int highScore, int level)
{
	if (!Node::init())
	{
		return false;
	}

	this->_pf = leftTopPoint;
	this->_u = u;
	this->highScore = highScore;
	this->level = level;

	score = 0;
	totalLinesClear = lineClearCount = 0;

	// add drawNodes
	DrawNode *tempDrawNode = DrawNode::create();
	this->addChild(tempDrawNode);
	bucketDrawNode = DrawNode::create();
	this->addChild(bucketDrawNode, -2);
	ghostDrawNode = DrawNode::create();
	this->addChild(ghostDrawNode, 1);
	movingTetDrawNode = DrawNode::create();
	this->addChild(movingTetDrawNode, 2);
	solidTetDrawNode = DrawNode::create();
	this->addChild(solidTetDrawNode, -1);

	// bucket walls
	// left wall
	tempDrawNode->drawRect(
		Vec2((bucketLeft - 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (bucketTop + t_const::BUCKET_TOP_GAP) * _u),
		Vec2(bucketLeft * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (bucketBottom - 1) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);
	// right wall
	tempDrawNode->drawRect(
		Vec2(bucketRight * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (bucketTop + t_const::BUCKET_TOP_GAP) * _u),
		Vec2((bucketRight + 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (bucketBottom - 1) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);
	// bottom bed
	tempDrawNode->drawRect(
		Vec2((bucketLeft - 1)* _u + _pf.x - _u / 2, _pf.y - _u / 2 - (bucketBottom - 1) * _u),
		Vec2((bucketRight + 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (bucketBottom) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);

	/* ---- this board area*/
	/*for (double i = 0; i < t_const::lm::NUM_OF_UNIT_BLOCKS_IN_WIDTH; ++i)
	{
		for (double j = 0; j < t_const::lm::NUM_OF_UNIT_BLOCKS_IN_HEIGHT; ++j)
		{
			tempDrawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, Color4F::ORANGE);
		}
	}*/

	return true;
}


void Board::start()
{
	// bucket inner grid	
	drawBucketInnerGrid();

	// add solidBlocks
	solidBlocks = SolidBlocks::create(bucketLeft, bucketRight, bucketTop, bucketBottom);
	this->addChild(solidBlocks);

	// add movable Tetromino
	movableTetromino = nullptr;
	this->generateBlock();

	// add update function to move movable tetris blocks
	schedule(CC_SCHEDULE_SELECTOR(Board::moveSchedular));
}


void Board::stop()
{
	unscheduleAllCallbacks();
	movableTetromino = nullptr;
	solidBlocks->clear();
}


void Board::movingBlockDown()
{
	if (movableTetromino != nullptr)
	{
		if (!movableTetromino->moveDown(*solidBlocks))
		{
			freezeMovableBlock();
		}
		else
		{
			drawMovingTetromino();
		}
	}
}


void Board::movingBlockLeft()
{
	if (movableTetromino != nullptr)
	{
		if (movableTetromino->moveLeft(*solidBlocks))
		{
			drawMovingTetromino();
			updateGhostPiece();
		}
	}
}


void Board::movingBlockRight()
{
	if (movableTetromino != nullptr)
	{
		if (movableTetromino->moveRight(*solidBlocks))
		{
			drawMovingTetromino();
			updateGhostPiece();
		}
	}
}


void Board::movingBlockRotate()
{
	if (movableTetromino != nullptr)
	{
		if (movableTetromino->rotateLeft(*solidBlocks))
		{
			drawMovingTetromino();
			updateGhostPiece();
		}
	}
}


void Board::movingBlockGravityDrop()
{
	if (movableTetromino != nullptr)
	{
		while (movableTetromino->checkMoveDown(*solidBlocks))
		{
			movableTetromino->moveDown(*solidBlocks);
		}
		freezeMovableBlock();
	}
}


// add movable block to solidBlocks and generate new Block
void Board::generateBlock()
{
	auto randNum = *randListIter;
	auto rotation = TetrominoTemplate::rotationTemplates->at(randNum)->getInitialRotation();
	auto color = TetrominoTemplate::colorTemplates->at(randNum);
	auto borderColor = TetrominoTemplate::borderColorTemplates->at(randNum);

	auto newBlock = Tetromino::create(_u, _pf, rotation, color, borderColor, spawnPoint);
	this->addChild(newBlock);
	movableTetromino = newBlock;
	drawMovingTetromino();
	createGhostPiece();
	drawBucketInnerGrid(color);
}


// helper function
void Board::freezeMovableBlock()
{
	ghostDrawNode->clear();
	auto temp = movableTetromino;
	movableTetromino = nullptr;		// setting movable block to nullptr freezes keyboard inputs & moveDown shedular
	solidBlocks->add(temp);
	drawSolidTetromino();
	movingTetDrawNode->clear();
	unschedule(CC_SCHEDULE_SELECTOR(Board::moveSchedular));
	schedule(CC_SCHEDULE_SELECTOR(Board::lineClearShedular));
}


void Board::drawMovingTetromino()
{
	movingTetDrawNode->clear();
	movableTetromino->draw(movingTetDrawNode);
}


void Board::drawSolidTetromino()
{
	solidTetDrawNode->clear();
	for (auto tetromino : solidBlocks->getSolidTetrominos())
	{
		tetromino->draw(solidTetDrawNode);
	}
}


void Board::drawBucketInnerGrid(cocos2d::Color4B color)
{
	for (double i = bucketLeft; i < bucketRight; ++i)
	{
		for (double j = bucketTop; j < bucketBottom; ++j)
		{
			bucketDrawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), t_const::POINT_SIZE, cocos2d::Color4F(color));
		}
	}
}

void Board::createGhostPiece()
{
	// remove old
	ghostDrawNode->clear();
	for (auto block : ghostPieces)
		this->removeChild(block);
	ghostPieces.clear();

	// get unitBlocksVec from movableTetromino
	for (auto block : movableTetromino->getUnitBlocksVec())
	{
		auto gBlock = UnitBlock::create(*block);
		this->addChild(gBlock);
		ghostPieces.push_front(gBlock);
	}

	// update 
	updateGhostPiece();
}

void Board::updateGhostPiece()
{
	// update position
	int i = 0;
	for (auto block : ghostPieces)
	{
		block->setPos(movableTetromino->getUnitBlocksVec().at(i)->currPos());
		++i;
	}

	// move down, till move down is not possible
	while ([&]() -> bool {
		for (auto block : ghostPieces)
			if (block->checkMoveDown(*solidBlocks) == false)
				return false;

		return true;
	}())
	{
		for (auto block : ghostPieces)
			block->moveDown();
	}

	// draw ghost
	ghostDrawNode->clear();
	for (auto block : ghostPieces)
		block->drawHollow(ghostDrawNode);
}


bool Board::checkGameOver()
{
	if (movableTetromino->checkMoveAt(*solidBlocks) == false)
	{
		notify(*this, TetrisEvent::GAMEOVER);
		stop();

		return true;
	}

	return false;
}


void Board::updateScore()
{
	// increase level
	if (lineClearCount >= t_const::LEVEL_CHANGE_LINE_CLEAR_COUNT)
	{
		++level;
		notify(*this, TetrisEvent::LEVEL_UP);
		lineClearCount = 0;

		// increase speed
		moveDelaySeconds *= t_const::SPEED_DECREASE;
	}

	score += (totalLinesClear * level * t_const::ONE_LINE_CLEAR_SCORE);
	notify(*this, TetrisEvent::SCORE_UP);
	totalLinesClear = 0;

	if (score > highScore)
	{
		highScore = score;
		notify(*this, TetrisEvent::HIGH_SCORE_UP);
	}

	// draw score
	cocos2d::log((std::to_string(score)).c_str());
	cocos2d::log((std::to_string(highScore)).c_str());
}


// shedulars
void Board::moveSchedular(float dt)
{
	if (toUpdate(dt))
	{
		tempDt = 0.0f;

		if (movableTetromino != nullptr)
		{
			if (!movableTetromino->moveDown(*solidBlocks))
			{
				freezeMovableBlock();
			}
			else
			{
				drawMovingTetromino();
			}
		}
	}
}


void Board::lineClearShedular(float dt)
{
	if (halfSecondUpdate(dt))
	{
		tempDt = 0.0f;

		auto numOfLinesCleared = solidBlocks->clearLines();
		lineClearCount += numOfLinesCleared;
		totalLinesClear += numOfLinesCleared;
		unschedule(CC_SCHEDULE_SELECTOR(Board::lineClearShedular));

		if (numOfLinesCleared > 0)
		{
			drawSolidTetromino();
			schedule(CC_SCHEDULE_SELECTOR(Board::dropHangingBlocksShedular));
		}
		else
		{
			if (totalLinesClear > 0)
				updateScore();

			notify(*this, TetrisEvent::INCREMENT_RAND_ITERATOR);
			generateBlock();
			if (checkGameOver() == false)
			{
				schedule(CC_SCHEDULE_SELECTOR(Board::moveSchedular));
			}
		}
	}
}


void Board::dropHangingBlocksShedular(float dt)
{
	if (halfSecondUpdate(dt))
	{
		tempDt = 0.0f;

		solidBlocks->dropHangingBlocks();
		drawSolidTetromino();
		unschedule(CC_SCHEDULE_SELECTOR(Board::dropHangingBlocksShedular));
		schedule(CC_SCHEDULE_SELECTOR(Board::lineClearShedular));
	}
}


bool Board::toUpdate(float dt)
{
	if ((tempDt += dt) >= moveDelaySeconds)
		return true;

	return false;
}


bool Board::halfSecondUpdate(float dt)
{
	if ((tempDt += dt) >= 0.5f)
		return true;

	return false;
}
