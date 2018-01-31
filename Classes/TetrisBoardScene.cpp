#include "TetrisBoardScene.h"
#include "Constants.h"
#include <algorithm>
#include <cstdlib>
#include "TetrisFont.h"

USING_NS_CC;

Layer *GameScene::ctLayer;

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

	initFromDB();
	int level = 1;
	// add board
	board = Board::createBoard(_u, _pf, randListIter, highScore, level);
	board->registerObserver(this);
	this->addChild(board);

	windowDrawNode = DrawNode::create();
	this->addChild(windowDrawNode);
	this->drawWindow();

	countDownLayer = nullptr;
	//countDown(visibleSize);

	auto testDrawNode = DrawNode::create();
	this->addChild(testDrawNode);
	auto testFont = TetrisFont::create("abcdefghijklmnopqrs", Color4F::GREEN, Vec2(0, visibleSize.height), 2.5, FontColorPattern::RANDOM_BLOCK);
	testFont->write(testDrawNode);

	return true;
}


void TetrisBoardScene::start()
{
	this->removeChild(countDownLayer);
	board->start();
}


int callback2(void *data, int argc, char **argv, char **azColName)
{
	int *d = (int*)data;
	*d = std::atoi(argv[0]);

	return 0;
}


void TetrisBoardScene::initFromDB()
{
	// get values from db
	highScore = 0;
	char *errorMsg;

	// open db
	if (sqlite3_open("tetris.db", &db))
	{
		cocos2d::log("can't open single_player_db database");
		cocos2d::log(sqlite3_errmsg(db));
	}
	else
	{
		cocos2d::log("single_player_db opend...");

		// get data from single_player_table
		char *query = "select score from sp where name = 'player';";

		int rc = sqlite3_exec(db, query, callback2, (void*)&highScore, &errorMsg);
		if (rc != SQLITE_OK)
		{
			cocos2d::log("sql error");
			cocos2d::log(errorMsg);
			sqlite3_free(errorMsg);
		}
		else
		{
			cocos2d::log("highscore loaded succefully");
		}

	}
	sqlite3_close(db);
}


void TetrisBoardScene::saveToDB()
{
	char *errorMsg;

	// save highScore to db
	if (sqlite3_open("tetris.db", &db))
	{
		cocos2d::log("can't open db");
		cocos2d::log(sqlite3_errmsg(db));
	}
	else
	{
		cocos2d::log("db opend...");
		// add data to single_player_table
		std::string query = "update sp set score = ";
		query.append(std::to_string(highScore));
		query.append(", max_level = ");
		query.append(std::to_string(maxLevel));
		query.append(" where name = 'player' ;");

		int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &errorMsg);
		if (rc != SQLITE_OK)
		{
			cocos2d::log("can't update db");
			cocos2d::log(errorMsg);
			sqlite3_free(errorMsg);
		}
		else
		{
			cocos2d::log("score updated in db");
		}
	}
	sqlite3_close(db);
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

		// save game highScore
		if (board.getScore() >= board.getHighScore())
		{
			this->highScore = board.getScore();
			this->maxLevel = board.getLevel();
			saveToDB();
		}
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

		board->movingBlockGravityDrop();

		break;

	default: break;

	}

}