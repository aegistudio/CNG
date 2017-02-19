#pragma once
#include <ncurses.h>
#include "box.h"

namespace cng {

class Pane : public Box {
	WINDOW* window, parent;
	Rect m_allocated, m_preferred;
public:
    virtual void allocate(Rect);

    virtual void deallocate();

	// Calculate the rect for interaction.
	virtual Rect rectInteract() const = 0;

	// Calculate the rect for render.
	virtual Rect rectRender() const = 0;

	// Tell the box that it is focused.
	virtual void focus(bool focused) const = 0;

	// Accept mouse input. The point is the point on screen.
	virtual void click(int key, Point point) = 0;
	virtual void release(int key, Point point) = 0;
	virtual void scroll(int offset, Point point) = 0;

	// Accept keyboard input. Only box on focus can receive input.
	virtual void keyboard(int key) = 0;

	// Repaint this box component.
	virtual void repaint() = 0;
};

}
