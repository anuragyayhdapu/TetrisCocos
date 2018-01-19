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
	//visibleSize.width /= 1.5;
	this->calcSceneDrawingData(_u, _pf, visibleSize);

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	// initialize with four values
	srand(time(NULL));
	for (short i = 0; i < 4; i++)
	{
		randList.push_back(rand() % TetrominoTemplate::size);
	}
	randListIter = randList.begin();

	// add board
	board = Board::createBoard(_u, _pf, randListIter);
	board->registerObserver(this);
	this->addChild(board);

	windowDrawNode = DrawNode::create();
	this->addChild(windowDrawNode);
	this->drawWindow();

	return true;
}


void TetrisBoardScene::onNotify(const Board & board, TetrisEvent _event)
{
	switch (_event)
	{
	case INCREMENT_RAND_ITERATOR:

		++randListIter;
		randList.push_back(rand() % TetrominoTemplate::size);
		randList.pop_front();
		redrawWindow();

		break;
	case GAMEOVER:
		// display game over scene

		// save game score
		break;
	default:
		break;
	}
}


void TetrisBoardScene::drawWindow()
{
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	drawNode->drawRect(
		Vec2(_pf.x + _u * (t_const::WINDOW_LEFT) - _u / 2, _pf.y - _u * (t_const::WINDOW_TOP)),
		Vec2(_pf.x + _u * (t_const::WINDOW_RIGHT), _pf.y - _u * (t_const::WINDOW_BOTTOM)),
		Color4F::ORANGE
	);
	redrawWindow();
}

void TetrisBoardScene::redrawWindow()
{
	windowDrawNode->clear();
	int i = 0;
	for (auto iter = ++randList.begin(); iter != randList.end(); ++iter)
	{
		auto tet = Tetromino::create(_u, _pf,
			TetrominoTemplate::rotationTemplates->at(*iter)->getInitialRotation(),
			TetrominoTemplate::colorTemplates->at(*iter),
			TetrominoTemplate::borderColorTemplates->at(*iter),
			BoardPos(t_const::WINDOW_LEFT + 1, (t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO * i) + t_const::WINDOW_TOP + 1)
		);

		tet->draw(windowDrawNode);

		++i;
	}
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