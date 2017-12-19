#pragma once

// Board Position data structure, 
// for easily maintaining blocks coordinates in TetrisBoard

struct BoardPos {
	BoardPos(int x, int y) { this->x = x; this->y = y; }
	int x, y;
};

struct BoardPosComparator {
	bool operator()(const BoardPos& left, const BoardPos& right) const
	{
		if (left.x == right.x) return left.y < right.y;
		else return left.x < right.x;
	}
};