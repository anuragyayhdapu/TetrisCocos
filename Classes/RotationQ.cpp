#include "RotationQ.h"

// hardcoded for now, change to generic if time permits
RotationQ::RotationQ(const std::array<BoardPos, 4> * top, const std::array<BoardPos, 4> * right,
	const std::array<BoardPos, 4> * bottom, const std::array<BoardPos, 4> * left)
{
	Rnode* topNode = new Rnode(top);
	Rnode* rightNode = new Rnode(right);
	Rnode* bottomNode = new Rnode(bottom);
	Rnode* leftNode = new Rnode(left);

	topNode->next = rightNode;
	rightNode->next = bottomNode;
	bottomNode->next = leftNode;
	leftNode->next = topNode;

	leftNode->prev = bottomNode;
	bottomNode->prev = rightNode;
	rightNode->prev = topNode;
	topNode->prev = leftNode;

	head = topNode;
	tail = leftNode;
}
