#pragma once

class SnakePair {
public:
	int x, y;
	SnakePair(int p_x, int p_y)
		: x(p_x), y(p_y) { }
	~SnakePair() {}
	bool operator==(const SnakePair&) const;
};
