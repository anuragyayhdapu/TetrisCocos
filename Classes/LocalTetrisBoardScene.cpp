#include "LocalTetrisBoardScene.h"
//#include "TetrominoTemplates.h"

USING_NS_CC;

bool LocalTetrisBoardScene::init()
{
	// super init
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->calcSceneDrawingData(_u, p1_pf, visibleSize, t_const::lm::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::lm::NUM_OF_UNIT_BLOCKS_IN_WIDTH);
	p1_pf.x = 0.05 * visibleSize.width;
	p2_pf.x = 0.60 * visibleSize.width;
	p1_pf.y = 0.90 * visibleSize.height;
	p2_pf.y = p1_pf.y;

	windowDrawNode = DrawNode::create();
	this->addChild(windowDrawNode);


	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(LocalTetrisBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	// initialize with four values
	srand(time(NULL));
	for (short i = 0; i < 4; i++)
	{
		randList.push_back(rand() % TetrominoTemplate::size);
	}
	p1RandListIter = randList.begin();
	p2RandListIter = randList.begin();

	// add boards
	p1Board = Board::createBoard(_u, p1_pf, p1RandListIter, 0, 1, t_const::lm::BUCKET_LEFT, t_const::lm::BUCKET_RIGHT, t_const::lm::BUCKET_TOP, t_const::lm::BUCKET_BOTTOM, t_const::lm::SPAWN_POSITION);
	p1Board->registerObserver(this);
	this->addChild(p1Board);
	p1Board->start();

	p2Board = Board::createBoard(_u, p2_pf, p2RandListIter, 0, 1, t_const::lm::BUCKET_LEFT, t_const::lm::BUCKET_RIGHT, t_const::lm::BUCKET_TOP, t_const::lm::BUCKET_BOTTOM, t_const::lm::SPAWN_POSITION);
	p2Board->registerObserver(this);
	this->addChild(p2Board);
	p2Board->start();

	drawWindow();


	return true;
}


void LocalTetrisBoardScene::onNotify(const Board & board, TetrisEvent _event)
{
	switch (_event)
	{
	case INCREMENT_RAND_ITERATOR:

		if (&board == p2Board)
			randListMoverHelper(p2RandListIter, p1RandListIter);
		else
			randListMoverHelper(p1RandListIter, p2RandListIter);

		break;
	case GAMEOVER:
		// TODO: figure this out later

		// display game over scene
		this->GoToGameOverScene(this);

		break;
	case LEVEL_UP:
		// TODO: figure this out later
		//lvlNum->reWrite(std::to_string(board.getLevel()), lvlNumDrawNode);
		break;
	case SCORE_UP:
		// TODO: figure this out later
		//scoreNum->reWrite(std::to_string(board.getScore()), scoreNumDrawNode);
		break;
	default:
		break;
	}
}


void LocalTetrisBoardScene::randListMoverHelper(std::list<short>::iterator & iterA, std::list<short>::iterator & iterB)
{
	// 1. if one to be incremented is equal, both are pointing to top
	// don't push_back, don't pop_front

	// 2. if one to be incremented is faster, 
	// then push if exceding 4, don't pop_front

	// 3. if one to be increased is slower, 
	// then push if faster one is less than 4, pop_front


	auto a = std::distance(randList.begin(), iterA);
	auto b = std::distance(randList.begin(), iterB);
	++iterA;

	// 1,2
	if (a >= randList.size() - 1)
		randList.push_back(rand() % TetrominoTemplate::size);
	// 3
	else if (a < b)
	{
		randList.pop_front();

		if (b < t_const::WINDOW_SIZE + 1)
			randList.push_back(rand() % TetrominoTemplate::size);
	}
}


void LocalTetrisBoardScene::drawWindow()
{
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	drawNode->drawRect(
		Vec2(p1_pf.x + _u * (t_const::lm::WINDOW_LEFT) - _u / 2, p1_pf.y - _u * (t_const::lm::WINDOW_TOP)),
		Vec2(p1_pf.x + _u * (t_const::lm::WINDOW_RIGHT), p1_pf.y - _u * (t_const::lm::WINDOW_BOTTOM)),
		Color4F::ORANGE
	);
	redrawWindow();
}


void LocalTetrisBoardScene::redrawWindow()
{
	// show in window positions 2, 3, and 4
	windowDrawNode->clear();
	int i = 0;
	for (auto iter = ++randList.begin(); i < 3; ++iter)
	{
		auto tet = Tetromino::create(_u, p1_pf,
			TetrominoTemplate::rotationTemplates->at(*iter)->getInitialRotation(),
			TetrominoTemplate::colorTemplates->at(*iter),
			TetrominoTemplate::borderColorTemplates->at(*iter),
			BoardPos(t_const::lm::WINDOW_LEFT + 1, (t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO * i) + t_const::lm::WINDOW_TOP + 1)
		);

		tet->draw(windowDrawNode);

		++i;
	}
}



void LocalTetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		p1Board->movingBlockDown();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		p1Board->movingBlockRight();
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		p1Board->movingBlockLeft();
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		p1Board->movingBlockRotate();
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		p1Board->movingBlockGravityDrop();
		break;

	default: break;

	}
}