#pragma once

#include "cocos2d.h"
#include "BoardPos.h"
#include "SolidBlocks.h"

/*
 * Basic building block of the world
 *	1. Can be relatively positioned in the grid
 *	2. Can be drawn
 *  3. Can be moved
 *	4. Has physics attached (pending {for now my own collision system})
 *	5. Initiates and interacts with Animation (pending)
 */

class SolidBlocks;

class UnitBlock : public cocos2d::Node
{
	//using SolidBlocksSet = const std::set<BoardPos, BoardPosComparator>&;

public:
	static double _u;	// size of one unit block
	static cocos2d::Vec2 _pf;	// // first middle point of a unit block in grid (point_first)

	UnitBlock();
	virtual ~UnitBlock();
	static UnitBlock* create(short x, short y, cocos2d::Color4B color, cocos2d::Color4B borderColor);
	bool init(short x, short y, cocos2d::Color4B color, cocos2d::Color4B borderColor);

	void drawBlock();

	/* check move functions, only checks if move is possible*/
	bool checkMoveDown(const SolidBlocks& solidBlocks);
	bool checkMoveLeft(const SolidBlocks& solidBlocks);
	bool checkMoveRight(const SolidBlocks& solidBlocks);
	static bool checkMoveAt(BoardPos nextPos, const SolidBlocks& solidBlocks);

	/*move functions; actually moves block by a unit, call check move function before to check for collision*/
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveAt(BoardPos pos);

	BoardPos currPos() { return BoardPos(_x, _y); }
	short getX() { return _x; }
	short getY() { return _y; }

	cocos2d::Color4B getColor() { return _color; }
	void clearDrawnBlock() { _drawNode->clear(); }

private:
	short _x, _y; // position of block in term of number of units
	cocos2d::DrawNode* _drawNode;
	cocos2d::Color4B _color;
	cocos2d::Color4B _borderColor;
};