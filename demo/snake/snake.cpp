// A snake game that use main loop only.
#include "cng/handler.h"
#include "cng/mainloop.h"
#include "snakepair.h"
#include "snakelogic.h"
#include "snakerender.h"
#include "curses.h"

#include <thread>
#include <chrono>

#pragma push(scroll)
#undef scroll

using namespace cng;

class SnakeLoop : public DefaultMainLoop {
public:
	virtual void init() {
		DefaultMainLoop::init();
		init_pair(SnakeColor::outline, COLOR_CYAN, COLOR_BLACK);
		init_pair(SnakeColor::snake, COLOR_GREEN, COLOR_BLACK);
		init_pair(SnakeColor::food, COLOR_YELLOW, COLOR_BLACK);
	}

} mainLoop;

class SnakeGame : public Handler, public SnakeLogic, public SnakeRender {
	bool paused = false;
public:
	SnakeGame(int _boundx, int _boundy)
		: SnakeLogic(_boundx, _boundy), SnakeRender() {}

	virtual void repaint() {
		if(paused)
			paintPause(*this);
		else {
			wclear(stdscr);
			paintGame(*this);
			paintBorder(*this);
		}
	}

	virtual void sync() override {
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
				rotate(SnakeDirection::dirUp);
			break;

			case KEY_DOWN:
				rotate(SnakeDirection::dirDown);
			break;

			case KEY_LEFT:
				rotate(SnakeDirection::dirLeft);
			break;

			case KEY_RIGHT:
				rotate(SnakeDirection::dirRight);
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
	std::thread([&] {
		while(true) {
			game.repaint();
			std::this_thread::sleep_for(
				std::chrono::milliseconds(100));
			if(!game.tick()) {
				mainLoop.enter(nullptr);
				break;
			}
		}
	}).detach();
	mainLoop.loopMain();
	return 0;
}
