#include "LocalTetrisBoardScene.h"

USING_NS_CC;

LocalTetrisBoardScene::LocalTetrisBoardScene()
	:
	p1_upP(true), p1_leftP(true), p1_rightP(true), p1_downP(true), p1_gdropP(true),
	leftScore(0), rightScore(0)
{
}

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
	p2_pf.x = 0.67 * visibleSize.width;
	p1_pf.y = 0.98 * visibleSize.height;
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
	addText();


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


void LocalTetrisBoardScene::randListMoverHelper(std::list<short>::iterator & iterA, std::list<short>::iterator & iterB)
{
	// 1. if one to be incremented is equal, both are pointing to top
	// don't push_back, don't pop_front

	// 2. if one to be incremented is faster, 
	// then push if exceding size of list, don't pop_front

	// 3. if one to be increased is slower, 
	// then push if faster one is less than 4, pop_front


	auto a = std::distance(randList.begin(), iterA);
	auto b = std::distance(randList.begin(), iterB);

	// 1, 2
	if (a >= randList.size() - 1)
	{
		randList.push_back(rand() % TetrominoTemplate::size);
	}
	++iterA;
	// 3
	if (a < b)
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

	auto p1r = p1_pf.x + t_const::lm::NUM_OF_UNIT_BLOCKS_IN_WIDTH * _u;
	auto d = p2_pf.x - p1r;
	short d_u = d / _u;
	PW = (d_u / 2) - (t_const::WINDOW_WIDTH / 2);

	drawNode->drawRect(
		Vec2(p1r + _u * PW - _u / 2, p1_pf.y - _u * (t_const::lm::WINDOW_TOP)),
		Vec2(p1r + _u * (PW + t_const::WINDOW_WIDTH), p1_pf.y - _u * (t_const::lm::WINDOW_BOTTOM)),
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
			BoardPos(PW + t_const::lm::NUM_OF_UNIT_BLOCKS_IN_WIDTH + 1, (t_const::NUM_OF_UNIT_BLOCKS_IN_TETROMINO * i) + t_const::lm::WINDOW_TOP + 1)
		);

		tet->draw(windowDrawNode);

		++i;
	}
}



void LocalTetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{

	case EventKeyboard::KeyCode::KEY_S:
		p1Board->movingBlockDown();
		if (p1_downP)
		{
			p1_down->freeze();
			p1_downP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_D:
		p1Board->movingBlockRight();
		if (p1_rightP)
		{
			p1_right->freeze();
			p1_rightP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_A:
		p1Board->movingBlockLeft();
		if (p1_leftP)
		{
			p1_left->freeze();
			p1_leftP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_W:
		p1Board->movingBlockRotate();
		if (p1_upP)
		{
			p1_up->freeze();
			p1_upP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
		p1Board->movingBlockGravityDrop();
		if (p1_gdropP)
		{
			p1_gdrop->freeze();
			p1_gdropP = false;
		}
		break;


		// board2
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		p2Board->movingBlockDown();
		if (p2_downP)
		{
			p2_down->freeze();
			p2_downP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		p2Board->movingBlockRight();
		if (p2_rightP)
		{
			p2_right->freeze();
			p2_rightP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		p2Board->movingBlockLeft();
		if (p2_leftP)
		{
			p2_left->freeze();
			p2_leftP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		p2Board->movingBlockRotate();
		if (p2_upP)
		{
			p2_up->freeze();
			p2_upP = false;
		}
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		p2Board->movingBlockGravityDrop();
		if (p2_gdropP)
		{
			p2_gdrop->freeze();
			p2_gdropP = false;
		}
		break;

	default: break;

	}
}


void LocalTetrisBoardScene::addText()
{
	// left player controls
	auto p1_up_y = (p1_pf.y - t_const::BUCKET_HEIGHT * _u) - _u;
	auto p1_up_x = p1_pf.x + ((t_const::BUCKET_WIDTH + 2) * _u) / 2;
	p1_up = TetrisButton::create("w", Vec2(p1_up_x, p1_up_y), 0.8f);
	p1_up->drawBorder();
	this->addChild(p1_up);
	p1_down = TetrisButton::create("s", Vec2(p1_up_x, p1_up_y - 2 *_u), 0.8f);
	p1_down->drawBorder();
	this->addChild(p1_down);
	p1_gdrop = TetrisButton::create("l shift", Vec2(p1_up_x, p1_up_y - 4 * _u), 0.5f);
	p1_gdrop->drawBorder();
	this->addChild(p1_gdrop);
	p1_right = TetrisButton::create("d", Vec2(p1_up_x + 2 * _u, p1_up_y - _u), 0.8f);
	p1_right->drawBorder();
	this->addChild(p1_right);
	p1_left = TetrisButton::create("a", Vec2(p1_up_x - 2 * _u, p1_up_y - _u), 0.8f);
	p1_left->drawBorder();
	this->addChild(p1_left);

	// right player controls
	auto p2_up_x = p2_pf.x + ((t_const::BUCKET_WIDTH + 2) * _u) / 2;
	p2_up = TetrisButton::create("#", Vec2(p2_up_x, p1_up_y), 0.8f);
	p2_up->drawBorder();
	this->addChild(p2_up);
	p2_down = TetrisButton::create("@", Vec2(p2_up_x, p1_up_y - 2 * _u), 0.8f);
	p2_down->drawBorder();
	this->addChild(p2_down);
	p2_gdrop = TetrisButton::create("r shift", Vec2(p2_up_x, p1_up_y - 4 * _u), 0.5f);
	p2_gdrop->drawBorder();
	this->addChild(p2_gdrop);
	p2_right = TetrisButton::create("$", Vec2(p2_up_x + 2 * _u, p1_up_y - _u), 0.8f);
	p2_right->drawBorder();
	this->addChild(p2_right);
	p2_left = TetrisButton::create("!", Vec2(p2_up_x - 2 * _u, p1_up_y - _u), 0.8f);
	p2_left->drawBorder();
	this->addChild(p2_left);

	// left player score
	txtDrawNode = DrawNode::create();
	this->addChild(txtDrawNode);

	auto p1_s_x = p1_pf.x + (t_const::BUCKET_WIDTH + 2) * _u;
	auto p1_s_y = Director::getInstance()->getVisibleSize().height * 0.5;
	leftScoreTxt = TetrisFont::create("score", cocos2d::Color4F::GRAY, Vec2(p1_s_x, p1_s_y), 0.40f, FontColorPattern::FULL, FontDrawPattern::SOLID);
	leftScoreTxt->write(txtDrawNode);
	leftScoreDrawNode = DrawNode::create();
	this->addChild(leftScoreDrawNode);
	leftScoreNum = TetrisFont::create(".", cocos2d::Color4F::GRAY, Vec2(p1_s_x, p1_s_y - 1.5 * _u), 0.60f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID);
	this->addChild(leftScoreNum);
	leftScoreNum->write(leftScoreDrawNode);

	// left player level
	leftLvlTxt = TetrisFont::create("level", cocos2d::Color4F::GRAY, Vec2(p1_s_x, p1_s_y - 4.5 * _u), 0.40f, FontColorPattern::FULL, FontDrawPattern::SOLID);
	leftLvlTxt->write(txtDrawNode);
	leftLvlDrawNode = DrawNode::create();
	this->addChild(leftLvlDrawNode);
	leftLvlNum = TetrisFont::create("1", cocos2d::Color4F::GRAY, Vec2(p1_s_x, p1_s_y - 6.0 * _u), 0.60f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID);
	this->addChild(leftLvlNum);
	leftLvlNum->write(leftLvlDrawNode);

	// right player score
	auto p2_s_x = p2_pf.x - _u;
	rightScoreTxt = TetrisFont::create("score", cocos2d::Color4F::GRAY, Vec2(p2_s_x, p1_s_y), 0.40f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT);
	rightScoreTxt->write(txtDrawNode);
	rightScoreDrawNode = DrawNode::create();
	this->addChild(rightScoreDrawNode);
	rightScoreNum = TetrisFont::create(".", cocos2d::Color4F::GRAY, Vec2(p2_s_x, p1_s_y - 1.5 * _u), 0.60f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::RIGHT);
	this->addChild(rightScoreNum);
	rightScoreNum->write(rightScoreDrawNode);

	// right player level
	rightLvlTxt = TetrisFont::create("level", cocos2d::Color4F::GRAY, Vec2(p2_s_x, p1_s_y - 4.5 * _u), 0.40f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT);
	rightLvlTxt->write(txtDrawNode);
	rightLvlDrawNode = DrawNode::create();
	this->addChild(rightLvlDrawNode);
	rightLvlNum = TetrisFont::create("1", cocos2d::Color4F::GRAY, Vec2(p2_s_x, p1_s_y - 6.0 * _u), 0.60f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::RIGHT);
	this->addChild(rightLvlNum);
	rightLvlNum->write(rightLvlDrawNode);

	// pause button
	auto pau_r = p1_pf.x + t_const::lm::NUM_OF_UNIT_BLOCKS_IN_WIDTH * _u;
	auto d = p2_pf.x - pau_r;
	auto pau_y = cocos2d::Director::getInstance()->getVisibleSize().height * 0.23;
	pauseBtn = TetrisButton::create([](cocos2d::Ref*) {cocos2d::log("pase clicked..."); }, "|",cocos2d::Color4F::ORANGE, Vec2(pau_r + d / 2, pau_y), 3.5f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 2);
	this->addChild(pauseBtn);
}