#include "nullGs.h"
using namespace cng;

NullGraphics nullGs;

static const Graphics& null() {
	return nullGs;
}

void NullGraphics::sync() {
	int scrwidth, scrheight;
	getmaxyx(m_window, scrheight, scrheight);
    m_rect.size.width = scrwidth;
    m_rect.size.height = scrheight;
}

void NullGraphics::snapCall(Point& point, std::function<void(int, int)> next) {
    sync();
    DefaultGraphics::snapCall(point, next);
}
