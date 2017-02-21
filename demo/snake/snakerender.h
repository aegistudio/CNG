#pragma once
#include "snakelogic.h"

enum SnakeColor {
	outline = 1,
	snake,
	food
};

class SnakeRender {
public:
	void paintGame(SnakeLogic&);

	void paintBorder(SnakeLogic&);

	void paintPause(SnakeLogic&);
};
