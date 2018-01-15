#include "TetrisBoardScene.h"
#include "Constants.h"
#include <algorithm>

USING_NS_CC;

bool TetrisBoardScene::init()
{
	// super init
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	visibleSize.width /= 1.5;
	this->calcSceneDrawingData(_u, _pf, visibleSize);

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);


	srand(time(NULL));

	// add board
	// for now, testing with one board
	board = Board::createBoard(_u, _pf);
	this->addChild(board);

	auto secondBoard = Board::createBoard(_u, Vec2(_pf.x + (visibleSize.width / 1.5), _pf.y));
	this->addChild(secondBoard);

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