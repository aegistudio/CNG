#include "snakerender.h"
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

void SnakeRender::paintGame(SnakeLogic& logic) {
	standout();
	attron(COLOR_PAIR(SnakeColor::snake));
	std::deque<SnakePair>::iterator iter;
	for(iter = logic.begin(); iter != logic.end(); iter ++) {
		SnakePair pair = *iter;
		mvprintw(pair.y + 1, 2 * pair.x + 1, "  ");
	}
	attroff(COLOR_PAIR(SnakeColor::snake));

	attron(COLOR_PAIR(SnakeColor::food));
	SnakePair food = logic.whereFood();
	mvprintw(food.y + 1, 2 * food.x + 1, "  ");
	standend();
	attroff(COLOR_PAIR(SnakeColor::food));
}

void SnakeRender::paintBorder(SnakeLogic& logic) {
	standout();
	attron(COLOR_PAIR(SnakeColor::outline));
	move(0, 1);
	for(int i = 1; i <= 2 * logic.boundx; i ++)
		addch(ACS_HLINE);

	move(logic.boundy + 1, 1);
	for(int i = 1; i <= 2 * logic.boundx; i ++)
		addch(ACS_HLINE);

	for(int i = 1; i <= logic.boundy + 1; i ++) {
		move(i, 0); 				addch(ACS_VLINE);
		move(i, 2 * logic.boundx + 1);	addch(ACS_VLINE);
	}

	int corny = logic.boundy + 1;
	int cornx = 2 * logic.boundx + 1;
	move(0, 0);			addch(ACS_ULCORNER);
	move(corny, 0);		addch(ACS_LLCORNER);
	move(corny, cornx);	addch(ACS_LRCORNER);
	move(0, cornx);		addch(ACS_URCORNER);
	attroff(COLOR_PAIR(SnakeColor::outline));
	standend();

	attron(COLOR_PAIR(SnakeColor::outline));
	char score[256];
	sprintf(score, " Score: %d ", logic.score());
	mvprintw(0, logic.boundx - strlen(score)/ 2, score);
	attroff(COLOR_PAIR(SnakeColor::outline));
}

void SnakeRender::paintPause(SnakeLogic& logic) {
	const char* pause0 = "+-----------+";
	const char* pause1 = "|   PAUSE   |";
	const char* pause2 = "+-----------+";
	int lenPause = strlen(pause1);
	int pausePosY = logic.boundy / 2;
	int pausePosX = 1 + logic.boundx - lenPause / 2;

	standout();
	attron(COLOR_PAIR(SnakeColor::outline));
	mvprintw(pausePosY - 1, pausePosX, pause0);
	mvprintw(pausePosY + 0, pausePosX, pause1);
	mvprintw(pausePosY + 1, pausePosX, pause2);
	attroff(COLOR_PAIR(SnakeColor::outline));
	standend();
}
