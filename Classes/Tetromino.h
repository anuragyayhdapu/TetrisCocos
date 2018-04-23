#pragma once

#include "UnitBlock.h"
#include "Constants.h"
#include "BoardPos.h"
#include "cocos2d.h"
#include "TetrominoTemplates.h"
#include "RotationQ.h"
#include "SolidBlocks.h"
#include <forward_list>
#include "message.pb.h"

class SolidBlocks;
class UnitBlock;

// base class for all tetrominos
class Tetromino : public cocos2d::Node
{
public:
	Tetromino();
	virtual ~Tetromino();
	static Tetromino* createWithNetworkData(double u, cocos2d::Vec2 pf, const tetris::proto::Tetromino&);
	bool initWithNetworkData(double u, cocos2d::Vec2 pf, const tetris::proto::Tetromino&);

	static Tetromino* createWithBlocks(const Tetromino& old, std::forward_list<BoardPos> blocksPos);
	bool initWithBlocks(const Tetromino& old, std::forward_list<BoardPos> blocksPos);
	
	static Tetromino* create(double u, cocos2d::Vec2 pf, RotationQ::Rnode* rotationQ, cocos2d::Color4B _color, cocos2d::Color4B _borderColor, BoardPos gridMatrixPoint);
	bool init(double u, cocos2d::Vec2 pf, RotationQ::Rnode* rotationQ, cocos2d::Color4B _color, cocos2d::Color4B _borderColor, BoardPos gridMatrixPoint);

	bool moveLeft(const SolidBlocks& solidBlocks);
	bool moveRight(const SolidBlocks& solidBlocks);
	bool moveDown(const SolidBlocks& solidBlocks);
	bool checkMoveDown(const SolidBlocks& solidBlocks) const;
	bool checkMoveAt(const SolidBlocks& solidBlocks) const;		// checks collision with solid blocks at cureent position of tetromino

	bool rotateRight(const SolidBlocks& solidBlocks);
	bool rotateLeft(const SolidBlocks& solidBlocks);

	void removeBlock(BoardPos pos);
	bool empty() { return unitBlocksVec.empty(); }
	void draw(cocos2d::DrawNode* drawNode);

	const std::vector<UnitBlock*>& getUnitBlocksVec() const { return unitBlocksVec; }

	void setTetColor(cocos2d::Color4B newColor) { color = newColor; }
	void setTetBorderColor(cocos2d::Color4B newColor) { borderColor = newColor; }
	void setGridMatrixPoint(BoardPos pos) { gridMatrixPoint = pos; }

	cocos2d::Color4B getNColor() const { return color; }
	cocos2d::Color4B getBorderColor() const { return borderColor; }
	BoardPos getGridMatrixPoint() const { return gridMatrixPoint; }

private:
	double u;
	cocos2d::Vec2 pf;
	std::vector<UnitBlock*> unitBlocksVec;
	BoardPos gridMatrixPoint;	// top left point of gridmatrix
	cocos2d::Color4B color;
	cocos2d::Color4B borderColor;

	RotationQ::Rnode * rotationQ;

	void rotate();
};