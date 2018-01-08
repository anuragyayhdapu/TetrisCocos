#pragma once

#include "BoardPos.h"
#include <vector>


// not a genric circularQ, 
// only for purposes of getting next & previous rotation
class RotationQ
{
public:
	//Node of Circular Q
	struct Rnode
	{
		Rnode *next, *prev;
		const std::array<BoardPos, 4> * face;

		Rnode(const std::array<BoardPos, 4> * _face) :
			face(_face), next(nullptr), prev(nullptr) {}
	};
	RotationQ(const std::array<BoardPos, 4> * top, const std::array<BoardPos, 4> * right,
		const std::array<BoardPos, 4> * bottom, const std::array<BoardPos, 4> * left);

	// getter
	Rnode* getInitialRotation() { return head; }
private:
	Rnode * head, * tail;
};