#include "RotationQ.h"

// hardcoded for now, change to generic if time permits
RotationQ::RotationQ(const std::vector<BoardPos> & top,const std::vector<BoardPos> & right,const std::vector<BoardPos> & bottom,const std::vector<BoardPos> & left)
{
	Node* topNode = new Node(top);
	Node* rightNode = new Node(right);
	Node* bottomNode = new Node(bottom);
	Node* leftNode = new Node(left);

	topNode->next = rightNode;
	rightNode->next = bottomNode;
	bottomNode->next = leftNode;
	leftNode->next = topNode;

	leftNode->prev = bottomNode;
	bottomNode->prev = rightNode;
	rightNode->prev = topNode;
	topNode->prev = leftNode;

	head = topNode;
}

const std::vector<BoardPos> & RotationQ::rotateRight()
{
	// change head position
	head = head->next;
	return head->face;
}

const std::vector<BoardPos> & RotationQ::rotateLeft()
{
	head = head->prev;
	return head->face;
}
