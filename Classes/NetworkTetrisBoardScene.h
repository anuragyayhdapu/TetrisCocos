#pragma once

#include "cocos2d.h"
#include "GameScene.h"
#include "Board.h"
#include "TetrisFont.h"
#include "TetrisButton.h"
#include "NetworkHandler.h"

class NetworkTetrisBoardScene : public GameScene
{
public:
	virtual bool init();
	CREATE_FUNC(NetworkTetrisBoardScene);

	void onNotify(const Board& board, TetrisEvent _event) {}

private:
	NetworkHandler networkHandler;
	Board * myBoard, *otherBoard;
	double _u;			// size of one unit block
	cocos2d::Vec2 _pf;	// first middle point of a unit block in grid
	std::list<short> randList;
	std::list<short>::iterator randListIter;
	TetrisFont *scoreTxt, *hScoreTxt, *lvlTxt, *scoreNum, *hScoreNum, *lvlNum;
	TetrisButton *up, *down, *left, *right, *gdrop;
	cocos2d::DrawNode *windowDrawNode, *txtDrawNode, *scoreNumDrawNode, *lvlNumDrawNode;

	void start();
	void drawWindow();
	void redrawWindow();
	void drawFonts();
	void addText(cocos2d::Size visibleSize);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// send and recieve data from network
	void sendMyBoardState();
	void recieveOtherBoardState();
};