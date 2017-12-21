#pragma once

#include "cocos2d.h"
#include "BoardPos.h"

/*
 * Basic building block of the world
 *	1. Can be relatively positioned in the grid 
 *	2. Can be drawn 
 *  3. Can be moved 
 *	4. Has physics attached (pending {for now my own collision system})
 *	5. Initiates and interacts with Animation (pending)
 */

class UnitBlock : public cocos2d::Node
{
public:
	static double _u;	// size of one unit block
	static cocos2d::Vec2 _pf;	// // first middle point of a unit block in grid (point_first)

	UnitBlock();
	virtual ~UnitBlock();
	virtual bool init();
	CREATE_FUNC(UnitBlock);
	static UnitBlock* createUnitBlock();
	
	void placeAt(int x = 0, int y = 0, cocos2d::Color4F color = cocos2d::Color4F::GRAY);
	
	/* check move functions, only checks if move is possible*/
	bool checkMoveDown(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);
	bool checkMoveLeft(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);
	bool checkMoveRight(const std::map<BoardPos, UnitBlock*, BoardPosComparator>& solidBlocks);

	/*move functions; actually moves block by a unit, call check move function before to check for collision*/
	void moveDown();
	void moveLeft();
	void moveRight();

	BoardPos currPos() { return BoardPos(_x, _y); }
	int getX() { return _x; }
	int getY() { return _y; }


private:
	int _x, _y; // position of block in term of number of units
	cocos2d::DrawNode* _drawNode;
	cocos2d::Color4F _color;

	/*draw functions; */
	void drawHollow();
	/*implement draw filled later, for now use drawHollow*/
	//void drawFilled(cocos2d::Color4F boundary, cocos2d::Color4F inside);
};