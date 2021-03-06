#include "defaultGs.h"
using namespace cng;

void DefaultGraphics::snapCall(Point& point, std::function<void(int, int)> next) {
	if(point.x < 0 || point.y < 0) return;
	if(point.x >= m_rect.size.width) return;
	if(point.y >= m_rect.size.height) return;
	int actualX = point.x + m_rect.location.x;
	int actualY = point.y + m_rect.location.y;
	next(actualX, actualY);
}

void DefaultGraphics::cursor(Point& point, int type) {
	snapCall(point, [&](int x, int y) {
		wmove(m_window, x, y); curs_set(type);
	});
}

void DefaultGraphics::put(Point& point, int character) {
	snapCall(point, [&](int x, int y) {
		mvwaddch(m_window, y, x, character);
    });
}

void DefaultGraphics::print(Point& point, int length, const char* text) {
	snapCall(point, [&](int x, int y) {
		mvwprintw(m_window, y, x, text);
	});
}

void DefaultGraphics::rowRepeat(Point& point, int times, int character) {
	for(int i = 0; i < times; i ++) {
		Point current = {point.x + i, point.y};
		put(current, character);
	}
}

void DefaultGraphics::columnRepeat(Point& point, int times, int character) {
	for(int i = 0; i < times; i ++) {
		Point current = {point.x, point.y + i};
		put(current, character);
	}
}

void DefaultGraphics::fill(Rect& rect, int character) {
    for(int i = 0; i < rect.size.height; i ++) {
		Point current = {rect.location.x, rect.location.y + i};
        columnRepeat(current, rect.size.width, character);
    }
}

DefaultGraphics& DefaultGraphics::create(Rect& rect) {
	Rect result = {0, 0, 0, 0};
	snapCall(rect.location, [&](int x, int y) {
		result.location.x = x;
		result.location.y = y;
		result.size.width = rect.size.width;
		result.size.height = rect.size.height;

		result.confine(m_rect);
	});
    return *(new DefaultGraphics(result, m_window));
}
