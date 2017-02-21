#pragma once

#include "types.h"

namespace cng {

// A graphics encapsulate the ncurses library
// and decide what a component can paint.

// It is usually used to create sub-view so
// that its underlying component can use it
// easily.

class Graphics {
public:
	// Control the character to print into
	// stand out mode or exit stand out mode.
	virtual void standout() = 0;
	virtual void standend() = 0;

	// Enable any attribute, such as color,
	// font, or so on.
	virtual void attron(int) = 0;
	virtual void attroff(int) = 0;

	// Set the cursor location and mode.
	virtual void cursor(Point&, int) = 0;

	// Print a character, a string, or a square of the 
	// same characters.
	virtual void put(Point&, int = ' ') = 0;
	virtual void print(Point&, int, const char*) = 0;
	virtual void rowRepeat(Point&, int, int = ' ') = 0;
	virtual void columnRepeat(Point&, int, int = ' ') = 0;
	virtual void fill(Rect&, int = ' ') = 0;

	// Create a sub graphics from its parent.
	virtual void create(Rect&) = 0;

	// The null graphics refers the window.
	// This is affected by the actual implementation
	// of your graphics system.

	// Please set flag _CNG_NODEFAULT_GS_ in order to 
	// disable the default implementation of the graphics. 
	// In this case you should implement your own graphics.
	static const Graphics& null();
};

}