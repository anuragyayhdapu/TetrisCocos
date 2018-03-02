#pragma once

#include "cocos2d.h"
#include "BoardPos.h"
#include "SolidBlocks.h"
#include "DrawData.h"


class SolidBlocks;

/*
 * Basic building block of the world
 */
class UnitBlock : public cocos2d::Node
{
	//using SolidBlocksSet = const std::set<BoardPos, BoardPosComparator>&;

public:
	double _u;	// size of one unit block
	cocos2d::Vec2 _pf;	// // first middle point of a unit block in grid (point_first)

	UnitBlock() {}
	virtual ~UnitBlock() {}
	static UnitBlock* create(const UnitBlock& block) {
		return create(block._u, block._pf, block._x, block._y, cocos2d::Color4B(block.drawData.color), cocos2d::Color4B(block.drawData.borderColor));
	}
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
	void setPos(BoardPos pos) { _x = pos.x, _y = pos.y; }
	short getX() { return _x; }
	short getY() { return _y; }
	void draw(cocos2d::DrawNode* drawNode);
	void drawHollow(cocos2d::DrawNode* drawNode);

private:
	short _x, _y; // position of block in term of number of units
	DrawData drawData;

	void calcDrawData();
};