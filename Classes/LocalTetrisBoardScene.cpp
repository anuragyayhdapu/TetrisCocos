#include "LocalTetrisBoardScene.h"
#include "LocalPauseScene.h"
#include "LocalGameOverScene.h"

USING_NS_CC;

LocalTetrisBoardScene::LocalTetrisBoardScene(MultiplayerGameMode gameMode, int timerMinutes)
	:
	leftScore(0), rightScore(0),
	gameMode(gameMode),
	timerMinutes(timerMinutes),
	timerSeconds(0)
{
}


LocalTetrisBoardScene * LocalTetrisBoardScene::create(MultiplayerGameMode gameMode, int timerMinutes)
{
	auto scene = new(std::nothrow)LocalTetrisBoardScene(gameMode, timerMinutes);
	if (scene && scene->init())
	{
		scene->autorelease();
	}
	else
	{
		delete scene;
		scene = nullptr;
	}
	return scene;
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

	initDrawNodes();

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

	p2Board = Board::createBoard(_u, p2_pf, p2RandListIter, 0, 1, t_const::lm::BUCKET_LEFT, t_const::lm::BUCKET_RIGHT, t_const::lm::BUCKET_TOP, t_const::lm::BUCKET_BOTTOM, t_const::lm::SPAWN_POSITION);
	p2Board->registerObserver(this);
	this->addChild(p2Board);

	drawWindow();
	countDownLayer = nullptr;

	if (gameMode != MultiplayerGameMode::RACE_AGAINS_TIME)
	{
		countDown(visibleSize);
	}
	else
	{
		addTimerButtons();
	}

	return true;
}


void LocalTetrisBoardScene::initDrawNodes()
{
	addChild(windowDrawNode = DrawNode::create());
	addChild(txtDrawNode = DrawNode::create(), 1);
	addChild(minuteDrawNode = DrawNode::create(), 1);
	addChild(secondDrawNode = DrawNode::create(), 1);
}


void LocalTetrisBoardScene::start()
{
	p1Board->start();
	p2Board->start();
	addText();
}

void LocalTetrisBoardScene::startWithTimer()
{
	removeChild(countDownLayer);
	removeChild(minusBtn);
	removeChild(plusBtn);
	removeChild(timerGameStartBtn);
	txtDrawNode->clear();
	minuteDrawNode->clear();
	secondDrawNode->clear();

	p1Board->start();
	p2Board->start();
	addText();

	schedule(CC_SCHEDULE_SELECTOR(LocalTetrisBoardScene::timerUpdateSchedular), 1.0f);
}



void LocalTetrisBoardScene::addTimerButtons()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	countDownLayer = LayerColor::create(Color4B(0, 0, 0, 128), visibleSize.width, visibleSize.height);
	countDownLayer->setPosition(Vec2(0, 0));
	this->addChild(countDownLayer);

	auto midpos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

	minuteTxt = TetrisFont::create(std::to_string(timerMinutes), cocos2d::Color4F::ORANGE, Vec2(midpos.x - _u, midpos.y), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT);
	this->addChild(minuteTxt);
	minuteTxt->write(minuteDrawNode);

	secondTxt = TetrisFont::create("00", cocos2d::Color4F::ORANGE, Vec2(midpos.x + _u, midpos.y), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::LEFT);
	this->addChild(secondTxt);
	secondTxt->write(secondDrawNode);

	auto dot = TetrisFont::create(":", cocos2d::Color4F::ORANGE, midpos, 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	dot->write(txtDrawNode);

	// add buttons
	// minus
	addChild(minusBtn = TetrisButton::create([&](cocos2d::Ref*) {
		if (timerMinutes > 1) --timerMinutes;
		minuteTxt->reWrite(timerMinutes, minuteDrawNode);
	}, "_", Color4F::BLUE, Vec2(midpos.x - 5 * _u, midpos.y), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// plus
	addChild(plusBtn = TetrisButton::create([&](cocos2d::Ref*) {
		if (timerMinutes < 10) ++timerMinutes;
		minuteTxt->reWrite(timerMinutes, minuteDrawNode);
	}, "+", Color4F::BLUE, Vec2(midpos.x + 6 * _u, midpos.y), 1.0f, FontAlign::LEFT, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));

	// start
	addChild(timerGameStartBtn = TetrisButton::create([&](cocos2d::Ref*) {
		startWithTimer();
	}, "start", Color4F::BLUE, Vec2(midpos.x, midpos.y - 4 * _u), 1.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID));
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
		switch (gameMode)
		{
		case LAST_MAN_STANDING:
			if (&board == p2Board)
				Director::getInstance()->replaceScene(LocalGameOverScene::create("left", "", gameMode));
			else
				Director::getInstance()->replaceScene(LocalGameOverScene::create("right", "", gameMode));
			break;

		case RACE_AGAINS_TIME:
		case ALL_ABOUT_SCORE:
			// calculate the highest score
			if (p1Board->getScore() == p2Board->getScore())
				Director::getInstance()->replaceScene(LocalGameOverScene::create(std::to_string(p1Board->getScore()), gameMode));
			else if (p1Board->getScore() > p2Board->getScore())
				Director::getInstance()->replaceScene(LocalGameOverScene::create("left", std::to_string(p1Board->getScore() - p2Board->getScore()), gameMode));
			else
				Director::getInstance()->replaceScene(LocalGameOverScene::create("right", std::to_string(p2Board->getScore() - p1Board->getScore()), gameMode));
			break;

		default:
			break;
		}

		break;

	case LEVEL_UP:
		if (&board == p1Board)
			leftLvlNum->reWrite(std::to_string(board.getLevel()), leftLvlDrawNode);
		else
			rightLvlNum->reWrite(std::to_string(board.getLevel()), rightLvlDrawNode);
		break;

	case SCORE_UP:
		if (gameMode != MultiplayerGameMode::LAST_MAN_STANDING) {

			if (&board == p1Board)
				leftScoreNum->reWrite(std::to_string(board.getScore()), leftScoreDrawNode);
			else
				rightScoreNum->reWrite(std::to_string(board.getScore()), rightScoreDrawNode);
		}
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


	size_t a = std::distance(randList.begin(), iterA);
	size_t b = std::distance(randList.begin(), iterB);

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

	window_left_x = p1r + _u * PW - _u / 2;
	window_right_x = p1r + _u * (PW + t_const::WINDOW_WIDTH);

	drawNode->drawRect(
		Vec2(window_left_x, p1_pf.y - _u * (t_const::lm::WINDOW_TOP)),
		Vec2(window_right_x, p1_pf.y - _u * (t_const::lm::WINDOW_BOTTOM)),
		Color4F::ORANGE
	);

	// draw arrow for next  tetromino
	leftArrowDrawNode = DrawNode::create();
	this->addChild(leftArrowDrawNode);
	auto l_x = window_left_x - _u;
	arrow_y = p1_pf.y - (t_const::lm::WINDOW_TOP + 1) * _u;

	leftArrow = TetrisFont::create("$", Color4F::GRAY, Vec2(l_x, arrow_y), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT);
	this->addChild(leftArrow);
	leftArrow->write(leftArrowDrawNode);

	rightArrowDrawNode = DrawNode::create();
	this->addChild(rightArrowDrawNode);
	auto r_x = window_right_x + _u;

	rightArrow = TetrisFont::create("!", Color4F::GRAY, Vec2(r_x, arrow_y), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID);
	this->addChild(rightArrow);
	rightArrow->write(rightArrowDrawNode);

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

	// reposition arrows
	calcArraowD(p1RandListIter, leftArrow, leftArrowDrawNode);
	calcArraowD(p2RandListIter, rightArrow, rightArrowDrawNode);
}


void LocalTetrisBoardScene::calcArraowD(std::list<short>::iterator & iter, TetrisFont* arrow, DrawNode* drawNode)
{
	size_t d = std::distance(randList.begin(), iter);

	if (d < 3)
		arrow->reDraw(drawNode, cocos2d::Vec2(arrow->getPos().x, arrow_y - (4 * d * _u)), cocos2d::Color4F::GRAY);
	else
	{
		d = 3;
		arrow->reDraw(drawNode, cocos2d::Vec2(arrow->getPos().x, arrow_y - (3.5 * d * _u)), cocos2d::Color4F::ORANGE);
	}
}



void LocalTetrisBoardScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{

	case EventKeyboard::KeyCode::KEY_S:
		p1Board->movingBlockDown();
		p1_down->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_D:
		p1Board->movingBlockRight();
		p1_right->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_A:
		p1Board->movingBlockLeft();
		p1_left->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_W:
		p1Board->movingBlockRotate();
		p1_up->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
		p1Board->movingBlockGravityDrop();
		p1_gdrop->freeze();
		break;


		// board2
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		p2Board->movingBlockDown();
		p2_down->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		p2Board->movingBlockRight();
		p2_right->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		p2Board->movingBlockLeft();
		p2_left->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		p2Board->movingBlockRotate();
		p2_up->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		p2Board->movingBlockGravityDrop();
		p2_gdrop->freeze();
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
	p1_down = TetrisButton::create("s", Vec2(p1_up_x, p1_up_y - 2 * _u), 0.8f);
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

	auto p1_s_x = p1_pf.x + (t_const::BUCKET_WIDTH + 2) * _u;
	auto p1_s_y = Director::getInstance()->getVisibleSize().height * 0.5;

	// left player score
	if (gameMode != MultiplayerGameMode::LAST_MAN_STANDING) {

		leftScoreTxt = TetrisFont::create("score", cocos2d::Color4F::GRAY, Vec2(p1_s_x, p1_s_y), 0.40f, FontColorPattern::FULL, FontDrawPattern::SOLID);
		leftScoreTxt->write(txtDrawNode);
		leftScoreDrawNode = DrawNode::create();
		this->addChild(leftScoreDrawNode);
		leftScoreNum = TetrisFont::create(".", cocos2d::Color4F::GRAY, Vec2(p1_s_x, p1_s_y - 1.5 * _u), 0.60f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID);
		this->addChild(leftScoreNum);
		leftScoreNum->write(leftScoreDrawNode);
	}

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
	if (gameMode != MultiplayerGameMode::LAST_MAN_STANDING) {

		rightScoreTxt = TetrisFont::create("score", cocos2d::Color4F::GRAY, Vec2(p2_s_x, p1_s_y), 0.40f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT);
		rightScoreTxt->write(txtDrawNode);
		rightScoreDrawNode = DrawNode::create();
		this->addChild(rightScoreDrawNode);
		rightScoreNum = TetrisFont::create(".", cocos2d::Color4F::GRAY, Vec2(p2_s_x, p1_s_y - 1.5 * _u), 0.60f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::RIGHT);
		this->addChild(rightScoreNum);
		rightScoreNum->write(rightScoreDrawNode);
	}

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
	auto pau_y = cocos2d::Director::getInstance()->getVisibleSize().height * 0.15;
	auto mid_x = pau_r + d / 2;
	auto pauseCallback = std::bind(&LocalTetrisBoardScene::goToPauseScene, this, std::placeholders::_1);
	pauseBtn = TetrisButton::create(pauseCallback, "|", cocos2d::Color4F::ORANGE, Vec2(mid_x, pau_y), 2.0f, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 2);
	this->addChild(pauseBtn);

	// timer
	if (gameMode == MultiplayerGameMode::RACE_AGAINS_TIME)
	{
		minuteTxt = TetrisFont::create(std::to_string(timerMinutes), cocos2d::Color4F::GRAY, Vec2(mid_x - 2 * _u, pau_y + 3 * _u), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT);
		this->addChild(minuteTxt);
		minuteTxt->write(minuteDrawNode);

		secondTxt = TetrisFont::create(std::to_string(timerSeconds), cocos2d::Color4F::GRAY, Vec2(mid_x, pau_y + 3 * _u), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::LEFT);
		this->addChild(secondTxt);
		secondTxt->write(secondDrawNode);

		auto dot = TetrisFont::create(":", cocos2d::Color4F::GRAY, Vec2(mid_x - _u, pau_y + 3 * _u), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
		dot->write(txtDrawNode);
	}
}


void LocalTetrisBoardScene::goToPauseScene(cocos2d::Ref * pSender)
{
	Director::getInstance()->pushScene(LocalPauseScene::create(std::to_string(p1Board->getScore()), std::to_string(p2Board->getScore()), gameMode));
}


void LocalTetrisBoardScene::timerUpdateSchedular(float dt)
{
	// reduce one second from timer
	// if timer reaches zero, call game over scene
	if (--timerSeconds < 0)
	{
		timerSeconds = 59;
		if (--timerMinutes < 0)
		{
			// copare board score
			if (p1Board->getScore() == p2Board->getScore())
				Director::getInstance()->replaceScene(LocalGameOverScene::create(std::to_string(p1Board->getScore()), gameMode));
			if (p1Board->getScore() > p2Board->getScore())
			{
				Director::getInstance()->replaceScene(LocalGameOverScene::create("left", std::to_string(p1Board->getScore()), gameMode));
			}
			else
				Director::getInstance()->replaceScene(LocalGameOverScene::create("right", std::to_string(p2Board->getScore()), gameMode));
		}
	}


	// redraw
	secondTxt->reWrite(timerSeconds, secondDrawNode);
	minuteTxt->reWrite(timerMinutes, minuteDrawNode);
}