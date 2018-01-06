#include "TetrisBoardScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
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
	schedule(schedule_selector(TetrisBoardScene::moveSchedular), moveDelaySeconds);

	/* ---- testing of unit grid*/
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	/*for (double i = 0; i < Constant::NUM_OF_UNIT_BLOCKS_IN_WIDTH; ++i)
	{
		for (double j = 0; j < Constant::NUM_OF_UNIT_BLOCKS_IN_HEIGHT; ++j)
		{
			drawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, Color4F::ORANGE);
		}
	}*/

	// bucket inner grid
	for (double i = Constant::BUCKET_LEFT; i < Constant::BUCKET_RIGHT; ++i)
	{
		for (double j = Constant::BUCKET_TOP; j < Constant::BUCKET_BOTTOM; ++j)
		{
			drawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, Color4F::MAGENTA);
		}
	}

	//auto gridLinesDrawNode = DrawNode::create(3.0F);
	//this->addChild(gridLinesDrawNode);
	//for (double i = Constant::BUCKET_LEFT; i < Constant::BUCKET_RIGHT; ++i)
	//{
	//	//gridLinesDrawNode->drawLine(Vec2(_pf.x, _u * Constant::BUCKET_BOTTOM), Vec2(), Color4F(Color4B(21, 21, 21, 255)));
	//}
	//for (double j = Constant::BUCKET_TOP; j < Constant::BUCKET_BOTTOM; ++j)
	//{
	//	double x1 = Constant::BUCKET_LEFT * _u + _pf.x;
	//	double x2 = Constant::BUCKET_RIGHT * _u + _pf.x;
	//	double y1 = Constant::BUCKET_TOP * _u + _pf.y + j * _u, y2 = y1;
	//	gridLinesDrawNode->drawLine(
	//		Vec2(x1, y1),
	//		Vec2(x2, y2),
	//		Color4F::GREEN/*Color4F(Color4B(21, 21, 21, 255))*/);
	//}


	// bucket walls
	// left wall
	drawNode->drawRect(
		Vec2((Constant::BUCKET_LEFT - 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (Constant::BUCKET_TOP + Constant::BUCKET_TOP_GAP) * _u),
		Vec2(Constant::BUCKET_LEFT * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (Constant::BUCKET_BOTTOM - 1) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);
	// right wall
	drawNode->drawRect(
		Vec2(Constant::BUCKET_RIGHT * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (Constant::BUCKET_TOP + Constant::BUCKET_TOP_GAP) * _u),
		Vec2((Constant::BUCKET_RIGHT + 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (Constant::BUCKET_BOTTOM - 1) * _u),
		Color4F(Color4B(105, 105, 105, 255))
	);
	// bottom bed
	drawNode->drawRect(
		Vec2((Constant::BUCKET_LEFT - 1)* _u + _pf.x - _u / 2, _pf.y - _u / 2 - (Constant::BUCKET_BOTTOM - 1) * _u),
		Vec2((Constant::BUCKET_RIGHT + 1) * _u + _pf.x - _u / 2, _pf.y - _u / 2 - (Constant::BUCKET_BOTTOM) * _u), 
		Color4F(Color4B(105, 105, 105, 255))
	);

	// add movable Tetromino
	srand(time(NULL));
	movableBlock = nullptr;
	this->generateBlock();

	// add solidBlocks
	solidBlocks = SolidBlocks::create();
	this->addChild(solidBlocks);


	return true;
}


void TetrisBoardScene::moveSchedular(float dt)
{
	if (movableBlock != nullptr)
	{
		if (!movableBlock->moveDown(*solidBlocks))
		{
			freezeMovableBlock();
		}
	}
}


void TetrisBoardScene::lineClearShedular(float dt)
{
	auto numOfLinesCleared = solidBlocks->clearLines();
	unschedule(schedule_selector(TetrisBoardScene::lineClearShedular));

	if (numOfLinesCleared > 0)
	{
		schedule(schedule_selector(TetrisBoardScene::dropHangingBlocksShedular), moveDelaySeconds);
	}
	else
	{
		generateBlock();
		schedule(schedule_selector(TetrisBoardScene::moveSchedular), moveDelaySeconds);
	}
	
}


void TetrisBoardScene::dropHangingBlocksShedular(float dt)
{
	solidBlocks->dropHangingBlocks();
	unschedule(schedule_selector(TetrisBoardScene::dropHangingBlocksShedular));
	schedule(schedule_selector(TetrisBoardScene::lineClearShedular), moveDelaySeconds);
}

void TetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (movableBlock != nullptr)
	{
		switch (keyCode)
		{

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:

			if (!movableBlock->moveDown(*solidBlocks))
			{
				freezeMovableBlock();
			}

			break;

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

			movableBlock->moveRight(*solidBlocks);

			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

			movableBlock->moveLeft(*solidBlocks);

			break;

		case EventKeyboard::KeyCode::KEY_Z:

			movableBlock->rotateLeft(*solidBlocks);

			break;

		case EventKeyboard::KeyCode::KEY_X:

			movableBlock->rotateRight(*solidBlocks);

			break;

		default: break;

		}
	}
}


// add movable block to solidBlocks and generate new Block
void TetrisBoardScene::generateBlock(int posX, int posY)
{
	int randNum = rand() % TetrominoTemplate::size;
	auto rotation = TetrominoTemplate::rotationTemplates.at(randNum);
	auto color = TetrominoTemplate::colorTemplates.at(randNum);
	auto borderColor = TetrominoTemplate::borderColorTemplates.at(randNum);

	auto newBlock = Tetromino::create(rotation, color, borderColor);
	newBlock->drawTetromino();
	this->addChild(newBlock);
	movableBlock = newBlock;
}


// helper function
void TetrisBoardScene::freezeMovableBlock()
{
	auto temp = movableBlock;
	movableBlock = nullptr;		// setting movable block to nullptr freezes keyboard inputs & moveDown shedular
	solidBlocks->add(temp);
	unschedule(schedule_selector(TetrisBoardScene::moveSchedular));
	schedule(schedule_selector(TetrisBoardScene::lineClearShedular), moveDelaySeconds);
}


void TetrisBoardScene::GoToPauseScene(cocos2d::Ref *pSender)
{
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void TetrisBoardScene::GoToGameOverScene(cocos2d::Ref *pSender)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(scene);
}