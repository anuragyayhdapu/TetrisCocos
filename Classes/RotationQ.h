#pragma once

#include "BoardPos.h"
#include <vector>

//Node of Circular Q
struct Node
{
	Node *next, *prev;
	const std::vector<BoardPos> face;

	Node(const std::vector<BoardPos> _face) :
		face(_face), next(nullptr), prev(nullptr) {}
};


// not a genric circularQ, 
// only for purposes of getting next & previous rotation
class RotationQ
{
public:
	RotationQ() { head = nullptr; }
	RotationQ(const std::vector<BoardPos>& top, const std::vector<BoardPos>& right, const std::vector<BoardPos>& bottom, const std::vector<BoardPos>& left);

	const std::vector<BoardPos>& nextRotation();
	const std::vector<BoardPos>& prevRotation();
	const std::vector<BoardPos>& currentRotation() { return head->face; }

private:
	Node * head;
};