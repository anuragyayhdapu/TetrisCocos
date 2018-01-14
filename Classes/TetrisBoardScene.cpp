#include "TetrisBoardScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Constants.h"
#include <algorithm>

USING_NS_CC;

double TetrisBoardScene::_u = 0;
Vec2 TetrisBoardScene::_pl = Vec2();
Vec2 TetrisBoardScene::_pf = Vec2();

TetrisBoardScene::TetrisBoardScene()
{
}

TetrisBoardScene::~TetrisBoardScene()
{
}

bool TetrisBoardScene::init()
{
	// super init
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// calculate _u, _pl, _pf
	double y = visibleSize.height, x = visibleSize.width;
	_u = 0;
	if (visibleSize.height < visibleSize.width)
	{
		_u = y / t_const::NUM_OF_UNIT_BLOCKS_IN_HEIGHT;
		x = _u * t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH;
	}
	else if (visibleSize.height >= visibleSize.width)
	{
		_u = x / t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH;
		y = _u * t_const::NUM_OF_UNIT_BLOCKS_IN_HEIGHT;
	}

	double xd = visibleSize.width - x;
	double yd = visibleSize.height - y;

	_pl = Vec2(xd / 2, (yd / 2) + y); // shifting this point from bottom left to top left
	_pf = Vec2(_pl.x + _u / 2, _pl.y - _u / 2);

	// set UnitBlock::_u & UnitBlock::_pf
	UnitBlock::_u = TetrisBoardScene::_u;
	UnitBlock::_pf = TetrisBoardScene::_pf;

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	/* ---- testing of unit grid*/
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);
	for (double i = 0; i < t_const::NUM_OF_UNIT_BLOCKS_IN_WIDTH; ++i)
	{
		for (double j = 0; j < t_const::NUM_OF_UNIT_BLOCKS_IN_HEIGHT; ++j)
		{
			drawNode->drawPoint(Vec2(i * _u + _pf.x, _pf.y - j * _u), 2, Color4F::ORANGE);
		}
	}


	srand(time(NULL));

	// add board
	// for now, testing with one board
	Board::_u = this->_u;
	Board::_pf = this->_pf;
	board = Board::createBoard(Vec2());
	this->addChild(board);


	return true;
}




void TetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{

	switch (keyCode)
	{

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:

		board->movingBlockDown();

		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		board->movingBlockRight();

		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		board->movingBlockLeft();

		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:

		board->movingBlockRotate();

		break;

	case EventKeyboard::KeyCode::KEY_SPACE:

		// configure hard drop later

		break;

	default: break;

	}

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