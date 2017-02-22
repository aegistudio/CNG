#include "snakerender.h"
#include "cng/graphics.h"
#include "cng/util.h"
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace cng;

SnakeRender::SnakeRender() {	}

SnakeRender::~SnakeRender() {	}

Rect rectGameView(SnakeLogic& logic) {
	return Rect(1, 1, 2 * logic.boundx, logic.boundy);
}

void SnakeRender::paintGame(SnakeLogic& logic) {
	Rect gameViewRect = rectGameView(logic);
    Graphics& gameView = Graphics::null().create(gameViewRect);

	standout();
	attron(COLOR_PAIR(SnakeColor::snake));
	std::deque<SnakePair>::iterator iter;
	for(iter = logic.begin(); iter != logic.end(); iter ++) {
		SnakePair pair = *iter;
		Point point = {2 * pair.x, pair.y};
		gameView.rowRepeat(point, 2);
	}
	attroff(COLOR_PAIR(SnakeColor::snake));

	attron(COLOR_PAIR(SnakeColor::food));
	SnakePair food = logic.whereFood();
	Point point = {2 * food.x, food.y};
	gameView.rowRepeat(point, 2);
	standend();
	attroff(COLOR_PAIR(SnakeColor::food));
}

void SnakeRender::paintBorder(SnakeLogic& logic) {
	Rect gameViewRect = rectGameView(logic);

	Point borderViewStart = gameViewRect.location;
	borderViewStart.x --; borderViewStart.y --;
	Dimension borderViewSize = gameViewRect.size;
	borderViewSize.width += 2;	borderViewSize.height +=2;

    Rect borderViewRect = {borderViewStart, borderViewSize};
	Graphics& borderView = Graphics::null().create(borderViewRect);

	standout();
	attron(COLOR_PAIR(SnakeColor::outline));

	cng::box(borderView, borderViewRect);

	attroff(COLOR_PAIR(SnakeColor::outline));
	standend();

	attron(COLOR_PAIR(SnakeColor::outline));
	char score[256];
	sprintf(score, " Score: %d ", logic.score());

    Point centerPoint = {borderViewSize.width / 2, 0};
    cng::center(borderView, centerPoint, score);

	attroff(COLOR_PAIR(SnakeColor::outline));
}

void SnakeRender::paintPause(SnakeLogic& logic) {
	Dimension pauseSize = {11, 3};
	Rect gameViewRect = rectGameView(logic);
	Rect pauseViewRect = cng::center(gameViewRect, pauseSize);
	Graphics& pauseView = Graphics::null().create(pauseViewRect);

	standout();
	attron(COLOR_PAIR(SnakeColor::outline));
	Rect innerRect = {{0, 0}, pauseSize};
	cng::box(pauseView, innerRect);
	cng::center(pauseView, innerRect, "  PAUSE  ");
	attroff(COLOR_PAIR(SnakeColor::outline));
	standend();
}
