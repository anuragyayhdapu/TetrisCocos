#include "TetrisCricketBoardScene.h"
#include "TetrominoTemplates.h"
#include "MainMenuScene.h"
#include "CricketGameOverScene.h"
#include "CricketPauseScene.h"

USING_NS_CC;

bool TetrisCricketBoardScene::init()
{
	if (!GameScene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->calcSceneDrawingData(_u, _pf, visibleSize, t_const::cr::NUM_OF_UNIT_BLOCKS_IN_HEIGHT, t_const::cr::NUM_OF_UNIT_BLOCKS_IN_WIDTH);
	_pf.x *= 1.1f;

	initDrawNodes();

	// set up keyboard event listner
	auto eventListner = EventListenerKeyboard::create();
	eventListner->onKeyPressed = CC_CALLBACK_2(TetrisCricketBoardScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListner, this);

	initBowlingList();

	// add boards
	addChild(board = Board::createBoard(_u, _pf, bowlingListIter, 0, 1, t_const::cr::BUCKET_LEFT, t_const::cr::BUCKET_RIGHT, t_const::cr::BUCKET_TOP, t_const::cr::BUCKET_BOTTOM, t_const::cr::SPAWN_POSITION));
	board->registerObserver(this);

	drawWindow();
	addChild(initLayer = TetrisCricketInitLayer::create([&](cocos2d::Ref*) {
		start();
		removeChild(initLayer);
	}));

	return true;
}

void TetrisCricketBoardScene::start()
{
	addText();
	board->start();
}

void TetrisCricketBoardScene::initDrawNodes()
{
	addChild(windowDrawNode = DrawNode::create());
	addChild(txtDrawNode = DrawNode::create());
	addChild(scoreDrawNode = DrawNode::create());
	addChild(lvlDrawNode = DrawNode::create());
	addChild(p1CapDrawNode = DrawNode::create());
	addChild(p2CapDrawNode = DrawNode::create());
	addChild(inningCapDrawNode = DrawNode::create());
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
	addChild(drawNode);

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
	addChild(arrow = TetrisFont::create("$", arrowDrawNode, Color4F::GRAY, Vec2(l_x, arrow_y), 1.0f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));

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

void TetrisCricketBoardScene::resetArrow()
{
	bowlingListIter = bowlingList.begin();
	redrawArrow();
}

void TetrisCricketBoardScene::redrawArrow()
{
	size_t d = std::distance(bowlingList.begin(), bowlingListIter);

	arrow->reDraw(arrowDrawNode, cocos2d::Vec2(arrow->getPos().x, arrow_y - (4 * d * _u)), cocos2d::Color4F::GRAY);
}

void TetrisCricketBoardScene::addText()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto y = visibleSize.height * 0.3;

	// window controls
	auto w_x = _pf.x - 7 * _u;
	addChild(w_up = TetrisButton::create("w", Vec2(w_x, y - 1.5 * _u), 1.0f));
	addChild(w_down = TetrisButton::create("s", Vec2(w_x, y - 3.5 * _u), 1.0f));
	addChild(TetrisFont::create("bowling", txtDrawNode, Color4F::GRAY, Vec2(w_x, y - 6.5 * _u), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(TetrisFont::create("controls", txtDrawNode, Color4F::GRAY, Vec2(w_x, y - 7.4 * _u), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	w_up->drawBorder();
	w_down->drawBorder();

	// bucket controls
	auto b_x = _pf.x + _u * (t_const::cr::NUM_OF_UNIT_BLOCKS_IN_WIDTH + 4);
	addChild(b_up = TetrisButton::create("#", Vec2(b_x, y), 1.0f));
	addChild(b_down = TetrisButton::create("@", Vec2(b_x, y - 2 * _u), 1.0f));
	addChild(b_gdrop = TetrisButton::create("[==]", Vec2(b_x, y - 4 * _u), 1.0f));
	addChild(b_right = TetrisButton::create("$", Vec2(b_x + 2 * _u, y - _u), 1.0f));
	addChild(b_left = TetrisButton::create("!", Vec2(b_x - 2 * _u, y - _u), 1.0f));
	addChild(TetrisFont::create("batting", txtDrawNode, Color4F::GRAY, Vec2(b_x, y - 6.5 * _u), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(TetrisFont::create("controls", txtDrawNode, Color4F::GRAY, Vec2(b_x, y - 7.4 * _u), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	b_up->drawBorder();
	b_down->drawBorder();
	b_gdrop->drawBorder();
	b_right->drawBorder();
	b_left->drawBorder();


	// score text
	addChild(TetrisFont::create("score", txtDrawNode, Color4F::GRAY, Vec2(b_x , visibleSize.height * 0.8), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(score = TetrisFont::create(".", scoreDrawNode, Color4F::GRAY, Vec2(b_x + 0.5 * _u, visibleSize.height * 0.8), 0.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));

	// Level text
	addChild(TetrisFont::create("level", txtDrawNode, Color4F::GRAY, Vec2(b_x , visibleSize.height * 0.74), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(level = TetrisFont::create("1", lvlDrawNode, Color4F::GRAY, Vec2(b_x + 0.5 * _u, visibleSize.height * 0.74), 0.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));

	// player caption
	addChild(pCaption1 = TetrisFont::create("player 1", p1CapDrawNode, Color4F::GRAY, Vec2(w_x, visibleSize.height * 0.40), 0.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(pCaption2 = TetrisFont::create("player 2", p2CapDrawNode, Color4F::GRAY, Vec2(b_x, visibleSize.height * 0.40), 0.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	currentInning;
	// pause button
	addChild(TetrisButton::create([&](Ref*) {
		Director::getInstance()->pushScene(CricketPauseScene::create(currentInning));
	}, "|", Color4F::RED, Vec2(visibleSize.width * 0.6, visibleSize.height * 0.14), 1.5, FontAlign::MIDDLE, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, 2));

	// inning caption
	addChild(inningCaption = TetrisFont::create("first", inningCapDrawNode, Color4F::GRAY, Vec2(w_x, visibleSize.height * 0.7), 0.9f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
	addChild(TetrisFont::create("inning", txtDrawNode, Color4F::GRAY, Vec2(w_x, visibleSize.height * 0.63), 0.7f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::MIDDLE));
}

void TetrisCricketBoardScene::initSecondInning()
{
	currentInning = CricketInnings::SECOND_INNING;

	// show switch layer
	addChild(switchLayer = TetrisCricketSwitchLayer::create([&](cocos2d::Ref*) {
		board->start();
		removeChild(switchLayer);
	}, score->getText()));

	// reset board
	board->stop();

	// reset arrow
	resetArrow();

	// switch player captions
	pCaption1->reWrite("player 2", p1CapDrawNode);
	pCaption2->reWrite("player 1", p2CapDrawNode);
	inningCaption->reWrite("second", inningCapDrawNode);

	// add target caption
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto b_x = _pf.x + _u * (t_const::cr::NUM_OF_UNIT_BLOCKS_IN_WIDTH + 4);
	addChild(TetrisFont::create("target", txtDrawNode, Color4F::GRAY, Vec2(b_x, visibleSize.height * 0.68), 0.5f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::RIGHT));
	addChild(target = TetrisFont::create(score->getText(), txtDrawNode, Color4F::GRAY, Vec2(b_x + 0.5 * _u, visibleSize.height * 0.68), 0.5f, FontColorPattern::RANDOM_BLOCK, FontDrawPattern::SOLID, FontAlign::LEFT));

	// reset score and level values
	score->reWrite(".", scoreDrawNode);
	level->reWrite("1", lvlDrawNode);
}

void TetrisCricketBoardScene::endGame()
{
	std::string winPlayer = "hoopla";
	int diff = 0;
	int scoreNum = std::atoi(score->getText().c_str());
	int targetNum = std::atoi(target->getText().c_str());
	
	if (scoreNum > targetNum)
	{
		winPlayer = "player 2";
		diff = scoreNum - targetNum;
	}
	else if (scoreNum < targetNum)
	{
		winPlayer = "player 1";
		diff = targetNum - scoreNum;
	}

	Director::getInstance()->replaceScene(CricketGameOverScene::create(diff, winPlayer));
}

void TetrisCricketBoardScene::onNotify(const Board & board, TetrisEvent _event)
{
	switch (_event)
	{
	case GAMEOVER:
		switch (currentInning)
		{
		case FIRST_INIINGS:
			if (board.getScore() == 0)
				score->reWrite("0", scoreDrawNode);
			initSecondInning();
			break;

		case SECOND_INNING:
			endGame();
			break;

			break;
		default:
			break;
		}

		break;

	case LEVEL_UP:
		level->reWrite(std::to_string(board.getLevel()), lvlDrawNode);
		break;

	case SCORE_UP:
		score->reWrite(std::to_string(board.getScore()), scoreDrawNode);
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
		w_up->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_S:
		moveArrowDown();
		w_down->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		board->movingBlockDown();
		b_down->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		board->movingBlockRight();
		b_right->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		board->movingBlockLeft();
		b_left->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		board->movingBlockRotate();
		b_up->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		board->movingBlockGravityDrop();
		b_gdrop->freeze();
		break;

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		//Director::getInstance()->replaceScene(TetrisCricketBoardScene::create());
		

		break;

	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		Director::getInstance()->replaceScene(MainMenuScene::create());
		break;


	default: break;

	}
}