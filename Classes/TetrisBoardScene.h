#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Observer.h"
#include "Board.h"
#include "Constants.h"
#include "TetrisFont.h"
#include <list>
//#include "sqlite3\include\sqlite3.h"
#include <sqlite3.h>

class TetrisBoardScene : public GameScene
{
public:
	virtual bool init();
	CREATE_FUNC(TetrisBoardScene);
	
	void onNotify(const Board& board, TetrisEvent _event);
	std::string getScore() { return scoreNum->getText(); }
	std::string getHighScore() { return hScoreNum->getText(); }
	std::string getLevel() { return lvlNum->getText(); }

private:
	sqlite3 * db;
	unsigned int highScore;
	int maxLevel;
	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;	// first middle point of a unit block in grid (point_first)
	Board* board;
	std::list<short> randList;					// randomly generated list to get next tetromino
	std::list<short>::iterator randListIter;	// randList iterators given to board 
	cocos2d::DrawNode* windowDrawNode;
	cocos2d::Layer *countDownLayer;
	TetrisFont *scoreTxt, *hScoreTxt, *lvlTxt, *scoreNum, *hScoreNum, *lvlNum;
	cocos2d::DrawNode *txtDrawNode, *scoreNumDrawNode, *hScoreNumDrawNode, *lvlNumDrawNode;

	void drawFonts(cocos2d::Size visibleSize);
	void drawWindow();
	void redrawWindow();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void start();

	void initFromDB();
	void saveToDB();
};