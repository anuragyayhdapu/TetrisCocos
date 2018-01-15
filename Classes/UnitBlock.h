#pragma once

#include "cocos2d.h"
#include "BoardPos.h"
#include "SolidBlocks.h"
#include "DrawData.h"

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
	double _u;	// size of one unit block
	cocos2d::Vec2 _pf;	// // first middle point of a unit block in grid (point_first)

	UnitBlock();
	//virtual ~UnitBlock();
	static UnitBlock* create(double u, cocos2d::Vec2 pf, short x, short y, cocos2d::Color4B color, cocos2d::Color4B borderColor);
	bool init(double u, cocos2d::Vec2 pf, short x, short y, cocos2d::Color4B color, cocos2d::Color4B borderColor);

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
	const DrawData& getDrawingData() const { return drawData; }

private:
	short _x, _y; // position of block in term of number of units
	DrawData drawData;

	void calcDrawData();
};