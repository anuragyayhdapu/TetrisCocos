#pragma once

// Board Position data structure, 
// for easily maintaining blocks coordinates in TetrisBoard

struct BoardPos {
	BoardPos() { x = 0; y = 0; }
	BoardPos(short x, short y) { this->x = x; this->y = y; }
	short x, y;

	BoardPos operator+ (const BoardPos& other)
	{
		return BoardPos(this->x + other.x, this->y + other.y);
	}

	BoardPos& operator+= (const BoardPos& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
};

struct BoardPosComparator {
	bool operator()(const BoardPos& left, const BoardPos& right) const
	{
		if (left.x == right.x) return left.y < right.y;
		else return left.x < right.x;
	}
};