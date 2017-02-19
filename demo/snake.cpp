// A snake game that use main loop only.
#include "cng/handler.h"
#include "cng/mainloop.h"

#include <curses.h>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#pragma push(scroll)
#undef scroll

using namespace cng;

#define TO_SNAKEPAIR(z, x, y)\
	z = x << 16 | y;
#define FROM_SNAKEPAIR(z, x, y)\
	x = z >>	 16;\
	y = z  & 0xffff;

class SnakeLoop : public DefaultMainLoop {
public:
	const short outline = 1;
	const short snake = 2;
	const short food = 3;

	virtual void init() {
		DefaultMainLoop::init();
		init_pair(outline, COLOR_CYAN, COLOR_BLACK);
		init_pair(snake, COLOR_GREEN, COLOR_BLACK);
		init_pair(food, COLOR_YELLOW, COLOR_BLACK);
	}

}mainLoop;

class SnakeGame : public Handler {
	bool paused = false;
	std::deque<int> location;
	int dirx = 1, diry = 0;
	int food;	int boundx, boundy;
	const int initLength = 4;
public:
	SnakeGame(int _boundx, int _boundy) :
		boundx(_boundx), boundy(_boundy) {

		TO_SNAKEPAIR(int x35, 3, 5);	location.push_front(x35);
		TO_SNAKEPAIR(int x45, 4, 5);	location.push_front(x45);
		TO_SNAKEPAIR(int x55, 5, 5);	location.push_front(x55);
		TO_SNAKEPAIR(int x65, 6, 5);	location.push_front(x65);

		srand(time(0));
		newFood();
	}

	void newFood() {
		int newx = rand() % boundx;
		int newy = rand() % boundy;
		TO_SNAKEPAIR(food, newx, newy);
	}

	void gameover() {
		mainLoop.enter(NULL);
	}

	void paintGame() {
		standout();
		attron(COLOR_PAIR(mainLoop.snake));
		std::deque<int>::iterator iter;
		for(iter = location.begin(); iter != location.end(); iter ++) {
			int posx, posy;
			FROM_SNAKEPAIR(*iter, posx, posy);
			mvprintw(posy + 1, 2 * posx + 1, "  ");
		}
		attroff(COLOR_PAIR(mainLoop.snake));

		attron(COLOR_PAIR(mainLoop.food));
		int foodx, foody;
		FROM_SNAKEPAIR(food, foodx, foody);
		mvprintw(foody + 1, 2 * foodx + 1, "  ");
		standend();
		attroff(COLOR_PAIR(mainLoop.food));
	}

	void paintBorder() {
		standout();
		attron(COLOR_PAIR(mainLoop.outline));
		move(0, 1);
		for(int i = 1; i <= 2 * boundx; i ++)
			addch(ACS_HLINE);

		move(boundy + 1, 1);
		for(int i = 1; i <= 2 * boundx; i ++)
			addch(ACS_HLINE);

		for(int i = 1; i <= boundy + 1; i ++) {
			move(i, 0); 				addch(ACS_VLINE);
			move(i, 2 * boundx + 1);	addch(ACS_VLINE);
		}

		int corny = boundy + 1;
		int cornx = 2 * boundx + 1;
		move(0, 0);			addch(ACS_ULCORNER);
		move(corny, 0);		addch(ACS_LLCORNER);
		move(corny, cornx);	addch(ACS_LRCORNER);
		move(0, cornx);		addch(ACS_URCORNER);
		attroff(COLOR_PAIR(mainLoop.outline));
		standend();

		attron(COLOR_PAIR(mainLoop.outline));
		char score[256];
		sprintf(score, " Score: %d ", location.size() - initLength);
		mvprintw(0, boundx - strlen(score)/ 2, score);
		attroff(COLOR_PAIR(mainLoop.outline));
	}

	virtual void sync() override {
		// Draw paused in the middle of screen.
		if(paused) {
			const char* pause0 = "+-----------+";
			const char* pause1 = "|   PAUSE   |";
			const char* pause2 = "+-----------+";
			int lenPause = strlen(pause1);
			int pausePosY = boundy / 2;
			int pausePosX = 1 + boundx - lenPause / 2;

			standout();
			attron(COLOR_PAIR(mainLoop.outline));
			mvprintw(pausePosY - 1, pausePosX, pause0);
			mvprintw(pausePosY + 0, pausePosX, pause1);
			mvprintw(pausePosY + 1, pausePosX, pause2);
			attroff(COLOR_PAIR(mainLoop.outline));
			standend();
			return;
		}

		// Move snake.
		int headPosX, headPosY;
		FROM_SNAKEPAIR(location.front(), headPosX, headPosY);

		headPosX += dirx;
		headPosY += diry;

		int newPosition;
		TO_SNAKEPAIR(newPosition, headPosX, headPosY);

		if(headPosX < 0 || headPosX >= boundx) { gameover(); return; }
		if(headPosY < 0 || headPosY >= boundy) { gameover(); return; }

		std::deque<int>::iterator iter;
		for(iter = location.begin(); iter != location.end(); iter ++)
			if(*iter == newPosition) { gameover(); return; }

		// Add new body portion.
		if(newPosition == food)
			newFood();
		else location.pop_back();

		location.push_front(newPosition);

		wclear(stdscr);
		paintGame();
		paintBorder();
	}

	virtual void click(int key, Point point) override {
	}
	virtual void release(int key, Point point) override {
	}
	virtual void scroll(int offset, Point point) override {
	}

	virtual void keyboard(int key) override {
		switch(key) {
			case KEY_UP:
				if(dirx) {
					dirx =  0;
					diry = -1;
				}
			break;

			case KEY_DOWN:
				if(dirx) {
					dirx =  0;
					diry = +1;
				}
			break;

			case KEY_LEFT:
				if(diry) {
					dirx = -1;
					diry =  0;
				}
			break;

			case KEY_RIGHT:
				if(diry){
					dirx = +1;
					diry =  0;
				}
			break;

			case ' ':
				paused = !paused;
			break;
		}
	}
};

#pragma pop(scroll)

int main() {
	SnakeGame game(32, 16);
	mainLoop.enter(&game);
	mainLoop.loopMain();
	return 0;
}
