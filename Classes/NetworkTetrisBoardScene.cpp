#include "NetworkTetrisBoardScene.h"

USING_NS_CC;

bool NetworkTetrisBoardScene::init()
{
	// super init
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->calcSceneDrawingData(_u, _pf, visibleSize, t_const::sp::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::sp::NUM_OF_UNIT_BLOCKS_IN_WIDTH);

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(NetworkTetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	// initialize with four values
	srand(time(NULL));
	//for (short i = 0; i < 4; i++)
	//{
	//	randList.push_back(rand() % TetrominoTemplate::size);
	//}
	//randListIter = randList.begin();

	//initFromDB();
	//int level = 1;
	//// add board
	//board = Board::createBoard(_u, _pf, randListIter, highScore, level, t_const::sp::BUCKET_LEFT, t_const::sp::BUCKET_RIGHT, t_const::sp::BUCKET_TOP, t_const::sp::BUCKET_BOTTOM, t_const::sp::SPAWN_POSITION);
	//board->registerObserver(this);
	//this->addChild(board);

	//windowDrawNode = DrawNode::create();
	//this->addChild(windowDrawNode);
	//this->drawWindow();
	//drawFonts(visibleSize);

	//countDownLayer = nullptr;
	//countDown(visibleSize);

	return true;
}

// initiate handshake before starting game
void NetworkTetrisBoardScene::handshake()
{
}

void NetworkTetrisBoardScene::start()
{
}

void NetworkTetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}
