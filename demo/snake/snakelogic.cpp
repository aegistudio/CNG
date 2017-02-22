#include "snakelogic.h"

#include <stdlib.h>
#include <time.h>

SnakePair up(0, -1), down(0, +1), left(-1, 0), right(+1, 0);

SnakeLogic::SnakeLogic(int _boundx, int _boundy)
	: boundx(_boundx), boundy(_boundy), food(0, 0) {

	location.push_front(SnakePair(3, 5));
	location.push_front(SnakePair(4, 5));
	location.push_front(SnakePair(5, 5));
	location.push_front(SnakePair(6, 5));

	srand(time(0));
	newFood();
	direction = &right;
	m_score = 0;
}

void SnakeLogic::newFood() {
    int newFoodX = rand() % boundx;
    int newFoodY = rand() % boundy;
    food = SnakePair(newFoodX, newFoodY);
}

std::deque<SnakePair>::iterator SnakeLogic::begin() {
	return location.begin();
}
std::deque<SnakePair>::iterator SnakeLogic::end() {
	return location.end();
}

void SnakeLogic::rotate(SnakeDirection p_direction) {
	switch(p_direction) {
		case SnakeDirection::dirUp:
			if(direction -> x != 0)
				direction = &up;
		break;

		case SnakeDirection::dirDown:
			if(direction -> x != 0)
				direction = &down;
		break;

		case SnakeDirection::dirLeft:
			if(direction -> y != 0)
				direction = &left;
		break;

		case SnakeDirection::dirRight:
			if(direction -> y != 0)
				direction = &right;
		break;
	}
}

bool SnakeLogic::tick() {
		// Move snake.
		SnakePair front = location.front();
		int headPosX = front.x, headPosY = front.y;

		headPosX += direction -> x;
		headPosY += direction -> y;

		if(headPosX < 0 || headPosX >= boundx) return false;
		if(headPosY < 0 || headPosY >= boundy) return false;

		SnakePair newPosition = {headPosX, headPosY};
		std::deque<SnakePair>::iterator iter;
		for(iter = begin(); iter != end(); iter ++)
			if(*iter == newPosition) return false;

		// Add new body portion.
		if(newPosition == food) {
			newFood();
			m_score ++;
		}
		else location.pop_back();

		location.push_front(newPosition);
		return true;
}
