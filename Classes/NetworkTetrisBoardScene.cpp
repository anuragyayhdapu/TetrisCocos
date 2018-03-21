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
	visibleSize.width *= 0.7f;
	this->calcSceneDrawingData(_u, _pf, visibleSize, t_const::sp::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::sp::NUM_OF_UNIT_BLOCKS_IN_WIDTH);
	_pf.x -= 2 * _u;

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(NetworkTetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	// initialize with four values
	srand(time(NULL));
	for (short i = 0; i < 4; i++)
	{
		randList.push_back(rand() % TetrominoTemplate::size);
	}
	randListIter = randList.begin();

	// add myBoard
	myBoard = Board::createBoard(_u, _pf, randListIter, 0, 1, t_const::sp::BUCKET_LEFT, t_const::sp::BUCKET_RIGHT, t_const::sp::BUCKET_TOP, t_const::sp::BUCKET_BOTTOM, t_const::sp::SPAWN_POSITION);
	myBoard->registerObserver(this);
	this->addChild(myBoard);

	// add other board
	auto pf2_x = _pf.x + _u * (t_const::sp::NUM_OF_UNIT_BLOCKS_IN_WIDTH + 2);
	auto pf2_y = _pf.y;
	auto _u2 = 0.8f * _u;
	otherBoard = Board::createNetworkBoard(_u2, Vec2(pf2_x, pf2_y), t_const::lm::BUCKET_LEFT, t_const::lm::BUCKET_RIGHT, t_const::lm::BUCKET_TOP, t_const::lm::BUCKET_BOTTOM);
	this->addChild(otherBoard);


	addChild(windowDrawNode = DrawNode::create());
	drawWindow();
	drawFonts();
	addText(visibleSize);

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


void NetworkTetrisBoardScene::drawWindow()
{
	auto drawNode = DrawNode::create();
	addChild(drawNode);

	drawNode->drawRect(
		Vec2(_pf.x + _u * (t_const::sp::WINDOW_LEFT) - _u / 2, _pf.y - _u * (t_const::sp::WINDOW_TOP)),
		Vec2(_pf.x + _u * (t_const::sp::WINDOW_RIGHT), _pf.y - _u * (t_const::sp::WINDOW_BOTTOM)),
		Color4F::ORANGE
	);
	redrawWindow();
}

void NetworkTetrisBoardScene::redrawWindow()
{
	windowDrawNode->clear();
	int i = 0;
	for (auto iter = ++randList.begin(); iter != randList.end(); ++iter)
	{
		auto tet = Tetromino::create(_u, _pf,
			TetrominoTemplate::rotationTemplates->at(*iter)->getInitialRotation(),
			TetrominoTemplate::colorTemplates->at(*iter),
			TetrominoTemplate::borderColorTemplates->at(*iter),
			BoardPos(t_const::sp::WINDOW_LEFT + 1, (t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO * i) + t_const::sp::WINDOW_TOP + 1)
		);

		tet->draw(windowDrawNode);

		++i;
	}
}

void NetworkTetrisBoardScene::drawFonts()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	addChild(txtDrawNode = DrawNode::create());
	addChild(scoreNumDrawNode = DrawNode::create());
	addChild(lvlNumDrawNode = DrawNode::create());

	addChild(scoreTxt = TetrisFont::create("score", txtDrawNode, cocos2d::Color4F::GRAY,
		Vec2(_pf.x + _u * (t_const::sp::WINDOW_RIGHT - 1), 0.4 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(lvlTxt = TetrisFont::create("level", txtDrawNode, cocos2d::Color4F::GRAY,
		Vec2(_pf.x + _u * (t_const::sp::WINDOW_RIGHT - 1), 0.2 * visibleSize.height), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));

	addChild(scoreNum = TetrisFont::create(".", scoreNumDrawNode, cocos2d::Color4F::GRAY,
		Vec2(_pf.x + _u * (t_const::sp::WINDOW_RIGHT), 0.4 * visibleSize.height), 0.6f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));
	addChild(lvlNum = TetrisFont::create("1", lvlNumDrawNode, cocos2d::Color4F::GRAY,
		Vec2(_pf.x + _u * (t_const::sp::WINDOW_RIGHT), 0.2 * visibleSize.height), 0.6f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));
}

void NetworkTetrisBoardScene::addText(Size visibleSize)
{
	// player controls
	/*auto x = 0.12 * visibleSize.width;
	auto y = visibleSize.height * 0.4;

	addChild(up = TetrisButton::create("#", Vec2(x, y), 1.0f));
	addChild(down = TetrisButton::create("@", Vec2(x, y - 2 * _u), 1.0f));
	addChild(gdrop = TetrisButton::create("[==]", Vec2(x, y - 4 * _u), 1.0f));
	addChild(right = TetrisButton::create("$", Vec2(x + 2 * _u, y - _u), 1.0f));
	addChild(left = TetrisButton::create("!", Vec2(x - 2 * _u, y - _u), 1.0f));

	up->drawBorder();
	down->drawBorder();
	gdrop->drawBorder();
	right->drawBorder();
	left->drawBorder();*/

	// arrow
	addChild(TetrisFont::create("!", txtDrawNode, Color4F::GRAY, Vec2(_pf.x + (t_const::sp::WINDOW_RIGHT + 1)* _u, visibleSize.height - 2 * _u), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID));
}

void NetworkTetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:

		//myBoard->movingBlockDown();
		//down->freeze();

		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		//myBoard->movingBlockRight();
		//right->freeze();

		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		//myBoard->movingBlockLeft();
		//left->freeze();

		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:

		//myBoard->movingBlockRotate();
		//up->freeze();

		break;

	case EventKeyboard::KeyCode::KEY_SPACE:

		//myBoard->movingBlockGravityDrop();
		//gdrop->freeze();

		break;

	default: break;

	}
}

void NetworkTetrisBoardScene::sendMyBoardState()
{
	
}

void NetworkTetrisBoardScene::recieveOtherBoardState()
{
}
