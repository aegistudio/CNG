#pragma once

#include "types.h"
#include "handler.h"
#include "ncurses.h"

namespace cng {

class Container;

class Component : public Handler {
public:
	// The parent allocate the position of the component
	// on screen. Please notice once the window get allocated,
	// it is considered to be validated.
	virtual void validate(Container&, Rect&) = 0;
	virtual void unvalidate();

	// Calculate the preferred size.
	virtual Rect preferred() const = 0;

	// Calculate the rect for interaction.
	virtual Rect interact() const = 0;

	// Calculate the rect for render.
	virtual Rect render() const = 0;

	// Tell the box that it is focused or unfocused.
	// Please notice that only when the component is
	// focused when it is able to receive keyboard
	// input, but any component can receive mouse 
	// input however.
	virtual void focus() = 0;
	virtual void unfocus() = 0;

	// Repaint this box component.
	// Please notice the Rect parameter refers to a region 
	// inside the component.
	virtual void repaint(Rect&) = 0;
};

}
