#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Observer.h"
#include "Board.h"
#include "TetrisButton.h"


class LocalTetrisBoardScene : public GameScene
{
public:
	LocalTetrisBoardScene(MultiplayerGameMode gameMode, int timerMinutes);
	static LocalTetrisBoardScene* create(MultiplayerGameMode gameMode, int timerMinutes = 1);
	virtual ~LocalTetrisBoardScene() {}

	void onNotify(const Board& board, TetrisEvent _event);

private:
	virtual bool init();
	MultiplayerGameMode gameMode;
	float window_left_x, window_right_x, l_arr_y, arrow_y;
	short PW;	// x position of window in BoardPos
	double _u;			// size of one unit block
	unsigned int leftScore, rightScore;
	cocos2d::Vec2 p1_pf, p2_pf;	// first middle point of a unit block in grid (point_first)
	Board *p1Board, *p2Board;
	std::list<short> randList;					// randomly generated list to get next tetromino
	std::list<short>::iterator p1RandListIter, p2RandListIter;	// randList iterators given to board
	cocos2d::DrawNode* windowDrawNode;
	TetrisButton *p1_up, *p1_left, *p1_right, *p1_down, *p1_gdrop, *p2_up, *p2_left, *p2_right, *p2_down, *p2_gdrop, *pauseBtn;
	boolean p1_upP, p1_leftP, p1_rightP, p1_downP, p1_gdropP, p2_upP, p2_leftP, p2_rightP, p2_downP, p2_gdropP;
	TetrisFont *leftScoreTxt, *rightScoreTxt, *leftScoreNum, *rightScoreNum, *leftLvlTxt, *rightLvlTxt, *leftLvlNum, *rightLvlNum, *rightArrow, *leftArrow;
	cocos2d::DrawNode *leftScoreDrawNode, *rightScoreDrawNode, *txtDrawNode, *leftLvlDrawNode, *rightLvlDrawNode, *rightArrowDrawNode, *leftArrowDrawNode;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void randListMoverHelper(std::list<short>::iterator& a, std::list<short>::iterator& b);		// 'a' iterator has moved
	void calcArraowD(std::list<short>::iterator & iter, TetrisFont* arrow, cocos2d::DrawNode* drawNode);

	void drawWindow();
	void redrawWindow();
	void addText();
	void start();
	void goToPauseScene(cocos2d::Ref * pSender);

	cocos2d::DrawNode *minuteDrawNode, *secondDrawNode;
	TetrisFont *minuteTxt, *secondTxt;
	int timerMinutes, timerSeconds;
	void timerUpdateSchedular(float dt);

	cocos2d::Layer *countDownLayer;
};