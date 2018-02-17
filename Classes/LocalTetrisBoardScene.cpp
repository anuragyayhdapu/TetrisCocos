#include "LocalTetrisBoardScene.h"
#include "TetrominoTemplates.h"

USING_NS_CC;

bool LocalTetrisBoardScene::init()
{
	// super init
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto drawSize = visibleSize;
	//drawSize.width /= 2;
	this->calcSceneDrawingData(_u, p1_pf, drawSize, t_const::lm::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::lm::NUM_OF_UNIT_BLOCKS_IN_WIDTH);
	p2_pf = p1_pf;
	p2_pf.x += drawSize.width;

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
	//p2RandListIter = randList.begin();

	Tetromino::spawnPoint = t_const::lm::SPAWN_POSITION;

	// add boards
	p1Board = Board::createBoard(_u, p1_pf, p1RandListIter, 0, 1, t_const::lm::BUCKET_LEFT, t_const::lm::BUCKET_RIGHT, t_const::lm::BUCKET_TOP, t_const::lm::BUCKET_BOTTOM);
	p1Board->registerObserver(this);
	this->addChild(p1Board);
	/*p2Board = Board::createBoard(_u, p2_pf, p1RandListIter, 0, 1, t_const::lm::BUCKET_LEFT, t_const::lm::BUCKET_RIGHT, t_const::lm::BUCKET_TOP, t_const::lm::BUCKET_BOTTOM);
	p2Board->registerObserver(this);
	this->addChild(p2Board);*/

	windowDrawNode = DrawNode::create();
	addChild(windowDrawNode);
	drawWindow();

	// TODO: remove after testing
	countDownLayer = nullptr;
	//countDown(visibleSize);

	p1Board->start();


	return true;
}

void LocalTetrisBoardScene::start()
{
	this->addButtons();
	this->removeChild(countDownLayer);
	p1Board->start();
	//p2Board->start();
}


void LocalTetrisBoardScene::onNotify(const Board & board, TetrisEvent _event)
{
	switch (_event)
	{
	case INCREMENT_RAND_ITERATOR:

		// TODO: figure this out later
		++p1RandListIter;
		randList.push_back(rand() % TetrominoTemplate::size);
		randList.pop_front();
		redrawWindow();

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


void LocalTetrisBoardScene::drawFonts(cocos2d::Size visibleSize)
{
	// TODO later
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
	windowDrawNode->clear();
	int i = 0;
	for (auto iter = ++randList.begin(); iter != randList.end(); ++iter)
	{
		auto tet = Tetromino::create(_u, p1_pf,
			TetrominoTemplate::rotationTemplates->at(*iter)->getInitialRotation(),
			TetrominoTemplate::colorTemplates->at(*iter),
			TetrominoTemplate::borderColorTemplates->at(*iter)
			//BoardPos(t_const::lm::WINDOW_LEFT + 1, (t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO * i) + t_const::lm::WINDOW_TOP + 1)
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