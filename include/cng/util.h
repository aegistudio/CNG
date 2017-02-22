#pragma once
#include "types.h"
#include "graphics.h"

#include <ncurses.h>
#include <string.h>

namespace cng {

// Draw a box into specific rect.
void box(Graphics& graphics, Rect& boxRect,
	int horizontalLine   = ACS_HLINE,
	int verticalLine     = ACS_VLINE,
	int upperLeftCorner  = ACS_ULCORNER,
	int upperRightCorner = ACS_URCORNER,
	int lowerLeftCorner  = ACS_LLCORNER,
	int lowerRightCorner = ACS_LRCORNER);

// Draw a string at the location which is the center.
void center(Graphics& graphics, Point& point,
	int length, const char* text);

inline void center(Graphics& graphics, Point& point,
	const char* text) {

    center(graphics, point, strlen(text), text);
}

inline void center(Graphics& graphics, Rect& rect,
	const char* text) {

    Point rectCenter = {
		rect.location.x + rect.size.width / 2,
		rect.location.y + rect.size.height / 2};
    center(graphics, rectCenter, strlen(text), text);
}

// Get the very center of the given rect.
Rect center(Rect&, Dimension&);

}
