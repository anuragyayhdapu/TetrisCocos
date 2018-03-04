#include "TetrisCricketBoardScene.h"
#include "TetrominoTemplates.h"

USING_NS_CC;

bool TetrisCricketBoardScene::init()
{
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->calcSceneDrawingData(_u, _pf, visibleSize, t_const::cr::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::cr::NUM_OF_UNIT_BLOCKS_IN_WIDTH);

	initDrawNodes();

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisCricketBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	initBowlingList();

	// add boards
	board = Board::createBoard(_u, _pf, bowlingListIter, 0, 1, t_const::cr::BUCKET_LEFT, t_const::cr::BUCKET_RIGHT, t_const::cr::BUCKET_TOP, t_const::cr::BUCKET_BOTTOM, t_const::cr::SPAWN_POSITION);
	board->registerObserver(this);
	this->addChild(board);

	drawWindow();
	start();

	return true;
}

void TetrisCricketBoardScene::start()
{
	board->start();
}

void TetrisCricketBoardScene::initDrawNodes()
{
	addChild(windowDrawNode = DrawNode::create());
}

void TetrisCricketBoardScene::initBowlingList()
{
	bowlingList.clear();

	for (int i = 0; i < TetrominoTemplate::size; i++)
	{
		bowlingList.push_back(i);
	}
	bowlingListIter = bowlingList.begin();
}


void TetrisCricketBoardScene::drawWindow()
{
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	auto window_left_x = _pf.x + t_const::cr::WINDOW_LEFT * _u;
	auto window_right_x = window_left_x + _u * t_const::WINDOW_WIDTH;

	drawNode->drawRect(
		Vec2(window_left_x, _pf.y - _u * (t_const::cr::WINDOW_TOP)),
		Vec2(window_right_x, _pf.y - _u * (t_const::cr::WINDOW_BOTTOM)),
		Color4F::ORANGE
	);

	// add arrow
	addChild(arrowDrawNode = DrawNode::create());
	auto l_x = window_left_x - _u;
	arrow_y = _pf.y - (t_const::lm::WINDOW_TOP + 1) * _u;

	addChild(arrow = TetrisFont::create("$", Color4F::GRAY, Vec2(l_x, arrow_y), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));

	arrow->write(arrowDrawNode);

	redrawWindow();
}

void TetrisCricketBoardScene::redrawWindow()
{
	// place tetrominos
	windowDrawNode->clear();
	int i = 0;
	for (auto iter : bowlingList)
	{
		auto tet = Tetromino::create(_u, _pf,
			TetrominoTemplate::rotationTemplates->at(iter)->getInitialRotation(),
			TetrominoTemplate::colorTemplates->at(iter),
			TetrominoTemplate::borderColorTemplates->at(iter),
			BoardPos(t_const::cr::WINDOW_LEFT + 1, (t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO * i) + t_const::cr::WINDOW_TOP + 1)
		);

		tet->draw(windowDrawNode);

		++i;
	}
}

void TetrisCricketBoardScene::moveArrowUp()
{
	if (bowlingListIter == bowlingList.begin())
	{
		bowlingListIter = bowlingList.end();
	}
	--bowlingListIter;
	redrawArrow();
}

void TetrisCricketBoardScene::moveArrowDown()
{
	if (++bowlingListIter == bowlingList.end())
	{
		bowlingListIter = bowlingList.begin();
	}

	redrawArrow();
}

void TetrisCricketBoardScene::redrawArrow()
{
	size_t d = std::distance(bowlingList.begin(), bowlingListIter);

	arrow->reDraw(arrowDrawNode, cocos2d::Vec2(arrow->getPos().x, arrow_y - (4 * d * _u)), cocos2d::Color4F::GRAY);
}

void TetrisCricketBoardScene::onNotify(const Board & board, TetrisEvent _event)
{
	switch (_event)
	{
	case INCREMENT_RAND_ITERATOR:

		break;

	case GAMEOVER:

		break;

	case LEVEL_UP:

		break;

	case SCORE_UP:

		break;

	default:
		break;
	}
}

void TetrisCricketBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		moveArrowUp();
		break;

	case EventKeyboard::KeyCode::KEY_S:
		moveArrowDown();
		break;

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
		board->movingBlockGravityDrop();
		break;

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->replaceScene(TetrisCricketBoardScene::create());
		break;




	default: break;

	}
}