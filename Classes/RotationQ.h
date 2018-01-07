#pragma once

#include "BoardPos.h"
#include <vector>


// not a genric circularQ, 
// only for purposes of getting next & previous rotation
class RotationQ
{
public:
	RotationQ() { head = nullptr; }
	RotationQ(const std::vector<BoardPos>& top, const std::vector<BoardPos>& right, const std::vector<BoardPos>& bottom, const std::vector<BoardPos>& left);
	~RotationQ();

	// getters
	const std::vector<BoardPos>& getRightRotation() { return head->next->face; }
	const std::vector<BoardPos>& getLeftRotation() { return head->prev->face; }
	const std::vector<BoardPos>& getCurrentRotation() { return head->face; }

	// for actually rotating
	const std::vector<BoardPos>& rotateRight();
	const std::vector<BoardPos>& rotateLeft();

private:

	//Node of Circular Q
	struct Node
	{
		Node *next, *prev;
		std::vector<BoardPos> face;

		Node(const std::vector<BoardPos> _face) :
			face(_face), next(nullptr), prev(nullptr) {}

		~Node() {
			next = nullptr;
			prev = nullptr;
			face.clear();
		}
	};
	Node * head;
};