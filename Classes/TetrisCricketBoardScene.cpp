#include "TetrisCricketBoardScene.h"
#include "TetrominoTemplates.h"
#include "MainMenuScene.h"

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


	addChild(initLayer = TetrisCricketInitLayer::create([&](cocos2d::Ref*) {removeChild(initLayer); }));


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

void TetrisCricketBoardScene::addText()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto y = visibleSize.height * 0.3;

	// window controls
	auto w_x = _pf.x - 4 * _u;
	addChild(w_up = TetrisButton::create("w", Vec2(w_x, y - 1.5 * _u), 1.0f));
	addChild(w_down = TetrisButton::create("s", Vec2(w_x, y - 3.5 * _u), 1.0f));
	auto f = TetrisFont::create("controls", Color4F::GRAY, Vec2(w_x, y - 6.5 * _u), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	addChild(f);
	f->write(txtDrawNode);

	// bucket controls
	auto b_x = _pf.x + _u * (t_const::cr::NUM_OF_UNIT_BLOCKS_IN_WIDTH + 4);
	addChild(b_up = TetrisButton::create("#", Vec2(b_x, y), 1.0f));
	addChild(b_down = TetrisButton::create("@", Vec2(b_x, y - 2 * _u), 1.0f));
	addChild(b_gdrop = TetrisButton::create("[==]", Vec2(b_x, y - 4 * _u), 1.0f));
	addChild(b_right = TetrisButton::create("$", Vec2(b_x + 2 * _u, y - _u), 1.0f));
	addChild(b_left = TetrisButton::create("!", Vec2(b_x - 2 * _u, y - _u), 1.0f));
	auto g = TetrisFont::create("controls", Color4F::GRAY, Vec2(b_x, y - 6.5 * _u), 0.4f, FontColorPattern::FULL, FontDrawPattern::SOLID, FontAlign::MIDDLE);
	addChild(g);
	g->write(txtDrawNode);

	w_up->drawBorder();
	w_down->drawBorder();
	b_up->drawBorder();
	b_down->drawBorder();
	b_gdrop->drawBorder();
	b_right->drawBorder();
	b_left->drawBorder();
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
		Director::getInstance()->replaceScene(TetrisCricketBoardScene::create());
		break;

	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		Director::getInstance()->replaceScene(MainMenuScene::create());
		break;


	default: break;

	}
}