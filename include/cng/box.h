#pragma once

#include "types.h"
#include "handler.h"
#include "ncurses.h"

namespace cng {

class Box : public Handler {
public:
	// The parent allocate the position of the component
	// on screen. Please notice once the window get allocated,
	// it is considered to be validated.
	virtual void allocate(Rect) = 0;
	virtual void deallocate() = 0;

	// Calculate the preferred size.
	virtual void rectPreferred() const = 0;

	// Calculate the rect for interaction.
	virtual Rect rectInteract() const = 0;

	// Calculate the rect for render.
	virtual Rect rectRender() const = 0;

	// Tell the box that it is focused.
	virtual void focus() = 0;
	virtual void unfocus() = 0;

	// Repaint this box component.
	virtual void repaint() = 0;
};

}
