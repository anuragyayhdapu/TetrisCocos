#include "Board.h"

USING_NS_CC;

Board::Board(std::list<short>::iterator& iter) :
	randListIter(iter)
{
}

Board::~Board()
{
}

Board * Board::createBoard(double u, Vec2 leftTopPoint, std::list<short>::iterator& randListIter)
{
	Board* board = new(std::nothrow)Board(randListIter);
	if (board && board->init(u, leftTopPoint, randListIter))
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

bool Board::init(double u, Vec2 leftTopPoint, std::list<short>::iterator& randListIter)
{
	if (!Node::init())
	{
		return false;
	}

	this->_pf = leftTopPoint;
	this->_u = u;

	// add update function to move movable tetris blocks
	moveDelaySeconds = 1.0f; // TODO: later change dynamically based on level
	schedule(schedule_selector(Board::moveSchedular), moveDelaySeconds);

	// bucket inner grid
	DrawNode *tempDrawNode = DrawNode::create();
	this->addChild(tempDrawNode);
	bucketDrawNode = DrawNode::create();
	this->addChild(bucketDrawNode);
	drawBucketInnerGrid();

	// add drawNodes
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

	// add movable Tetromino
	movableBlock = nullptr;
	this->generateBlock();

	// add solidBlocks
	solidBlocks = SolidBlocks::create();
	this->addChild(solidBlocks);

	return true;
}


void Board::movingBlockDown()
{
	if (movableBlock != nullptr)
	{
		if (!movableBlock->moveDown(*solidBlocks))
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
	if (movableBlock != nullptr)
	{
		if (movableBlock->moveLeft(*solidBlocks))
		{
			drawMovingTetromino();
		}
	}
}


void Board::movingBlockRight()
{
	if (movableBlock != nullptr)
	{
		if (movableBlock->moveRight(*solidBlocks))
		{
			drawMovingTetromino();
		}
	}
}


void Board::movingBlockRotate()
{
	if (movableBlock != nullptr)
	{
		if (movableBlock->rotateLeft(*solidBlocks))
		{
			drawMovingTetromino();
		}
	}
}


void Board::movingBlockGravityDrop()
{
	if (movableBlock != nullptr)
	{
		// configure for hard drop

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
	movableBlock = newBlock;
	drawMovingTetromino();
	drawBucketInnerGrid(color);
}


// helper function
void Board::freezeMovableBlock()
{
	auto temp = movableBlock;
	movableBlock = nullptr;		// setting movable block to nullptr freezes keyboard inputs & moveDown shedular
	solidBlocks->add(temp);
	drawSolidTetromino();
	movingTetDrawNode->clear();
	unschedule(schedule_selector(Board::moveSchedular));
	schedule(schedule_selector(Board::lineClearShedular), moveDelaySeconds);
}


void Board::drawMovingTetromino()
{
	movingTetDrawNode->clear();
	movableBlock->draw(movingTetDrawNode);
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


// shedulars
void Board::moveSchedular(float dt)
{
	if (movableBlock != nullptr)
	{
		if (!movableBlock->moveDown(*solidBlocks))
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
	unschedule(schedule_selector(Board::lineClearShedular));

	if (numOfLinesCleared > 0)
	{
		drawSolidTetromino();
		schedule(schedule_selector(Board::dropHangingBlocksShedular), moveDelaySeconds);
	}
	else
	{
		notify(*this, TetrisEvent::INCREMENT_RAND_ITERATOR);
		generateBlock();
		schedule(schedule_selector(Board::moveSchedular), moveDelaySeconds);
	}

}


void Board::dropHangingBlocksShedular(float dt)
{
	solidBlocks->dropHangingBlocks();
	drawSolidTetromino();
	unschedule(schedule_selector(Board::dropHangingBlocksShedular));
	schedule(schedule_selector(Board::lineClearShedular), moveDelaySeconds);
}