#include "nullGs.h"
using namespace cng;

NullGraphics nullGs;

Graphics& Graphics::null() {
	return nullGs;
}

void NullGraphics::sync() {
	m_window = stdscr;
	int scrwidth, scrheight;
	getmaxyx(m_window, scrheight, scrwidth);
    m_rect.size.width = scrwidth;
    m_rect.size.height = scrheight;
}

void NullGraphics::snapCall(Point& point, std::function<void(int, int)> next) {
    sync();
    DefaultGraphics::snapCall(point, next);
}
