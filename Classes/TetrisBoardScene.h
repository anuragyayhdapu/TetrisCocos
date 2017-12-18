#pragma once

#include "cocos2d.h"
#include "UnitBlock.h"

class TetrisBoardScene : public cocos2d::Scene
{
public:
	TetrisBoardScene();
	virtual bool init();
	static TetrisBoardScene* createTetrisBoardScene();

	CREATE_FUNC(TetrisBoardScene);

	virtual ~TetrisBoardScene();

private:

	static double _u;				// size of one unit block
	static cocos2d::Vec2 _pl;		// left-top point in grid (point_left)
	static cocos2d::Vec2 _pf;		// first middle point of a unit block in grid (point_first)
	static int moveDelaySeconds;	// speed at which block moves
	UnitBlock* movableBlock;		// only one movable block at a time
	struct BoardPos {
		BoardPos(int x, int y) { this->x = x; this->y = y; }
		int x, y;
	};
	struct BoardPosComparator {
		bool operator()(const BoardPos& left, const BoardPos& right) const
		{
			if (left.x == right.x) return left.y < right.y;
			else return left.x < right.x;
		}
	};
	std::map<BoardPos, UnitBlock*, BoardPosComparator> solidBlocks;	// immovable blocks laying down over bed

	static const int NUM_OF_UNIT_BLOCKS_IN_HEIGHT = 30;
	static const int NUM_OF_UNIT_BLOCKS_IN_WIDTH = 25;

	void UpdateFunction(float dt);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void generateBlock(int posX = TetrisBoardScene::NUM_OF_UNIT_BLOCKS_IN_WIDTH / 2, int posY = 0);
};