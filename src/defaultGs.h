#pragma once
#include "ncurses.h"
#include "cng/graphics.h"

#include <functional>

namespace cng {

// The default implementation of Graphics.
class DefaultGraphics : public Graphics {
protected:
	WINDOW* m_window;
	Rect m_rect;
public:
	DefaultGraphics(Rect rect, WINDOW* window = stdscr):
		m_window(window), m_rect(rect) {}

	// Calculate the actual coordinate, and post the invocation to the next.
	virtual void snapCall(Point& point, std::function<void(int, int)> next);

	virtual void cursor(Point&, int) override;

	virtual void put(Point&, int = ' ') override;

	virtual void print(Point&, int, const char*) override;

	virtual void rowRepeat(Point&, int, int = ' ') override;

	virtual void columnRepeat(Point&, int, int = ' ') override;

	virtual void fill(Rect&, int = ' ') override;

	virtual DefaultGraphics& create(Rect&) override;
};

}
