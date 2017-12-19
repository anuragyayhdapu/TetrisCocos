#include "TetrisBoardScene.h"
#include <algorithm>

USING_NS_CC;

double TetrisBoardScene::_u = 0;
Vec2 TetrisBoardScene::_pl = Vec2();
Vec2 TetrisBoardScene::_pf = Vec2();
int TetrisBoardScene::moveDelaySeconds = 0;

TetrisBoardScene::TetrisBoardScene()
{
}

TetrisBoardScene::~TetrisBoardScene()
{
}

TetrisBoardScene * TetrisBoardScene::createTetrisBoardScene()
{
	return TetrisBoardScene::create();
}

bool TetrisBoardScene::init()
{
	// super init
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	double yv = visibleSize.height, xv = visibleSize.width;

	// calculate _u, _pl, _pf
	double y = yv, x = xv;
	_u = 0;
	if (yv < xv)
	{
		_u = y / Constant::NUM_OF_UNIT_BLOCKS_IN_HEIGHT;
		x = _u * Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH;
	}
	else if (yv >= xv)
	{
		_u = x / Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH;
		y = _u * Constant::NUM_OF_UNIT_BLOCKS_IN_HEIGHT;
	}

	double xd = xv - x;
	double yd = yv - y;

	_pl = Vec2(xd / 2, (yd / 2) + y); // shifting this point from bottom left to top left
	_pf = Vec2(_pl.x + _u / 2, _pl.y - _u / 2);

	// set UnitBlock::_u & UnitBlock::_pf
	UnitBlock::_u = TetrisBoardScene::_u;
	UnitBlock::_pf = TetrisBoardScene::_pf;

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	// add update function to move movable tetris blocks
	TetrisBoardScene::moveDelaySeconds = 1.0;	// TODO: later change dynamically based on level
	schedule(schedule_selector(TetrisBoardScene::UpdateFunction), moveDelaySeconds);

	/* ---- testing of unit grid*/
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	for (double i = 0; i < Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH; ++i)
	{
		for (double j = 0; j < Constant::NUM_OF_UNIT_BLOCKS_IN_HEIGHT; ++j)
		{
			drawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, Color4F::ORANGE);
		}
	}

	/* ---- testing of movable nodes */
	this->movableBlock = UnitBlock::createUnitBlock();
	movableBlock->placeAt(Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH / 2, 0);
	this->addChild(movableBlock);

	return true;
}


void TetrisBoardScene::UpdateFunction(float dt)
{
	if (!movableBlock->moveDown(solidBlocks))
	{
		generateBlock();
	}
}

void TetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	bool blockMoved = true;

	switch (keyCode)
	{
		// only move blocks within boundary

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		// not allowed, or may be allowed as a special power
		//blockMoved = movableBlock->moveUp(solidBlocks);
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		blockMoved = movableBlock->moveDown(solidBlocks);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		blockMoved = movableBlock->moveRight(solidBlocks);
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		blockMoved = movableBlock->moveLeft(solidBlocks);
		break;

	default: break;

	}

	if (!blockMoved)
	{
		generateBlock();
	}
}


// add movable block to solidBlocks and generate new Block
void TetrisBoardScene::generateBlock(int posX, int posY)
{
	BoardPos movableBlockPos(movableBlock->getX(), movableBlock->getY());
	solidBlocks[movableBlockPos] = movableBlock;
	movableBlock = nullptr;

	auto newBlock = UnitBlock::createUnitBlock();
	newBlock->placeAt(posX, posY);
	this->addChild(newBlock);
	movableBlock = newBlock;
}