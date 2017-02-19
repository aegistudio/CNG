#pragma once
#include "types.h"

namespace cng {

class Handler {
public:
	virtual void sync() = 0;

	// Accept mouse input. The point is the point within the component.
	virtual void click(int key, Point point) = 0;
	virtual void release(int key, Point point) = 0;
	virtual void scroll(int offset, Point point) = 0;

	// Accept keyboard input. Only box on focus can receive input.
	virtual void keyboard(int key) = 0;
};

}
