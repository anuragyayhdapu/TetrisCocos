#include "Board.h"

USING_NS_CC;

Board::Board(std::list<short>::iterator& iter) :
	randListIter(iter)
{
}

Board::~Board()
{
}

Board * Board::createBoard(double u, Vec2 leftTopPoint, std::list<short>::iterator& randListIter, unsigned int highScore, int level)
{
	Board* board = new(std::nothrow)Board(randListIter);
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
	moveDelaySeconds = 1.0f; // TODO: later change dynamically based on level
	testDelaySeconds = 0.9f;

	// add drawNodes
	DrawNode *tempDrawNode = DrawNode::create();
	this->addChild(tempDrawNode);
	bucketDrawNode = DrawNode::create();
	this->addChild(bucketDrawNode);
	ghostDrawNode = DrawNode::create();
	this->addChild(ghostDrawNode);
	movingTetDrawNode = DrawNode::create();
	this->addChild(movingTetDrawNode);
	solidTetDrawNode = DrawNode::create();
	this->addChild(solidTetDrawNode);

	// bucket walls
	// left wall
	tempDrawNode->drawRect(
		Vec2((t_const::BUCKET_LEFT - 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (t_const::BUCKET_TOP + t_const::BUCKET_TOP_GAP) * _u),
		Vec2(t_const::BUCKET_LEFT * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (t_const::BUCKET_BOTTOM - 1) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);
	// right wall
	tempDrawNode->drawRect(
		Vec2(t_const::BUCKET_RIGHT * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (t_const::BUCKET_TOP + t_const::BUCKET_TOP_GAP) * _u),
		Vec2((t_const::BUCKET_RIGHT + 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (t_const::BUCKET_BOTTOM - 1) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);
	// bottom bed
	tempDrawNode->drawRect(
		Vec2((t_const::BUCKET_LEFT - 1)* _u + _pf.x - _u / 2, _pf.y - _u / 2 - (t_const::BUCKET_BOTTOM - 1) * _u),
		Vec2((t_const::BUCKET_RIGHT + 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (t_const::BUCKET_BOTTOM) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);

	/* ---- this board area*/
	/*for (double i = 0; i < t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH; ++i)
	{
		for (double j = 0; j < t_const::NUM_OF_UNIT_BLOCKS_IN_HEIGHT; ++j)
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
	solidBlocks = SolidBlocks::create();
	this->addChild(solidBlocks);

	// add movable Tetromino
	movableTetromino = nullptr;
	this->generateBlock();

	// add update function to move movable tetris blocks
	schedule(CC_SCHEDULE_SELECTOR(Board::moveSchedular), moveDelaySeconds);
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

	auto newBlock = Tetromino::create(_u, _pf, rotation, color, borderColor);
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
	schedule(CC_SCHEDULE_SELECTOR(Board::lineClearShedular), testDelaySeconds);
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
	for (double i = t_const::BUCKET_LEFT; i < t_const::BUCKET_RIGHT; ++i)
	{
		for (double j = t_const::BUCKET_TOP; j < t_const::BUCKET_BOTTOM; ++j)
		{
			bucketDrawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, cocos2d::Color4F(color));
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


void Board::lineClearShedular(float dt)
{
	auto numOfLinesCleared = solidBlocks->clearLines();
	lineClearCount += numOfLinesCleared;
	totalLinesClear += numOfLinesCleared;
	unschedule(CC_SCHEDULE_SELECTOR(Board::lineClearShedular));

	if (numOfLinesCleared > 0)
	{
		drawSolidTetromino();
		schedule(CC_SCHEDULE_SELECTOR(Board::dropHangingBlocksShedular), testDelaySeconds);
	}
	else
	{
		if (totalLinesClear > 0)
			updateScore();

		notify(*this, TetrisEvent::INCREMENT_RAND_ITERATOR);
		generateBlock();
		if (checkGameOver() == false)
		{
			schedule(CC_SCHEDULE_SELECTOR(Board::moveSchedular), moveDelaySeconds);
		}
	}

}


void Board::dropHangingBlocksShedular(float dt)
{
	solidBlocks->dropHangingBlocks();
	drawSolidTetromino();
	unschedule(CC_SCHEDULE_SELECTOR(Board::dropHangingBlocksShedular));
	schedule(CC_SCHEDULE_SELECTOR(Board::lineClearShedular), testDelaySeconds);
}