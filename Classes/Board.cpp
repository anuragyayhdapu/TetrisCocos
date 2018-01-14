#include "Board.h"

USING_NS_CC;

double Board::_u = 0;
Vec2 Board::_pf = Vec2();

Board::Board()
{
}

Board::~Board()
{
}

Board * Board::createBoard(Vec2 leftTopPoint)
{
	Board* board = new(std::nothrow)Board();
	if (board && board->init(leftTopPoint))
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

bool Board::init(Vec2 leftTopPoint)
{
	if (!Node::init())
	{
		return false;
	}

	this->leftTopPoint = leftTopPoint;

	// add update function to move movable tetris blocks
	moveDelaySeconds = 1.0f; // TODO: later change dynamically based on level
	schedule(schedule_selector(Board::moveSchedular), moveDelaySeconds);

	// bucket inner grid
	DrawNode *tempDrawNode = DrawNode::create();
	this->addChild(tempDrawNode);
	for (double i = t_const::BUCKET_LEFT; i < t_const::BUCKET_RIGHT; ++i)
	{
		for (double j = t_const::BUCKET_TOP; j < t_const::BUCKET_BOTTOM; ++j)
		{
			tempDrawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, Color4F::MAGENTA);
		}
	}

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
	if (movableBlock->moveLeft(*solidBlocks))
	{
		drawMovingTetromino();
	}
}


void Board::movingBlockRight()
{
	if (movableBlock->moveRight(*solidBlocks))
	{
		drawMovingTetromino();
	}
}


void Board::movingBlockRotate()
{
	if (movableBlock->rotateLeft(*solidBlocks))
	{
		drawMovingTetromino();
	}
}


void Board::movingBlockGravityDrop()
{
	// configure for hard drop
}


// add movable block to solidBlocks and generate new Block
void Board::generateBlock()
{
	int randNum = rand() % TetrominoTemplate::size;
	auto rotation = TetrominoTemplate::rotationTemplates->at(randNum)->getInitialRotation();
	auto color = TetrominoTemplate::colorTemplates->at(randNum);
	auto borderColor = TetrominoTemplate::borderColorTemplates->at(randNum);

	auto newBlock = Tetromino::create(rotation, color, borderColor);
	this->addChild(newBlock);
	movableBlock = newBlock;
	drawMovingTetromino();
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
	drawingHelper(movableBlock, movingTetDrawNode);
}


void Board::drawSolidTetromino()
{
	solidTetDrawNode->clear();
	for (auto tetromino : solidBlocks->getSolidTetrominos())
	{
		drawingHelper(tetromino, solidTetDrawNode);
	}
}


void Board::drawingHelper(const Tetromino* tetromino, DrawNode* drwaNode)
{
	for (auto block : tetromino->getUnitBlocksVec())
	{
		auto dd = block->getDrawingData();
		drwaNode->drawSolidRect(dd.origin, dd.destination, dd.color);
		drwaNode->drawRect(dd.origin, dd.destination, cocos2d::Color4F::BLACK);
		drwaNode->drawPoint(dd.midPoint, 5.0f, cocos2d::Color4F::BLACK);
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