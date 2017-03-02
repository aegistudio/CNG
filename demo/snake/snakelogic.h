#pragma once
#include "snakepair.h"
#include <deque>

enum class SnakeDirection {
	dirUp = 0,
	dirDown,
	dirLeft,
	dirRight
};

class SnakeLogic {
	std::deque<SnakePair> location;
	SnakePair *direction, *prevDirection;
	SnakePair food;
	int m_score;

	void newFood();
public:
	const int boundx, boundy;
	SnakeLogic(int _boundx, int _boundy);

	bool tick();

	std::deque<SnakePair>::iterator begin();
	std::deque<SnakePair>::iterator end();

	void rotate(SnakeDirection);

	SnakePair whereFood() const { return food; }
	int score() const { return m_score; };
};
