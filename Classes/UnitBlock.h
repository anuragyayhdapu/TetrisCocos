#pragma once

#include "cocos2d.h"

/*
 * Basic building block of the world
 *	1. Can be relatively positioned in the grid 
 *	2. Can be drawn (pending) 
 *  3. Can be moved (pending)
 *	4. Has physics attached (pending)
 *	5. Initiates and interacts with Animation (pending)
 */

class UnitBlock : public cocos2d::Node
{
public:
	UnitBlock();
	virtual bool init();
	static UnitBlock* createunitBlock();

	/*move functions; move by a unit*/
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	/*draw functions; */
	void drawHollow(cocos2d::Color4F color);
	void drawFilled(cocos2d::Color4F boundary, cocos2d::Color4F inside);

	CREATE_FUNC(UnitBlock);

	virtual ~UnitBlock();

	static double _u;	// size of one unit block
	static cocos2d::Vec2 _pf;	// // first middle point of a unit block in grid (point_first)
private:
	int _x, _y; // position of block in term of number of units
	cocos2d::DrawNode* _drawNode;

};