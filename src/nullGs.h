#pragma once
#include "defaultGs.h"

namespace cng {

class NullGraphics : public DefaultGraphics {
public:
	NullGraphics() : DefaultGraphics(Rect(0, 0, 0, 0)) {}
    ~NullGraphics() {}

	// Sync up with the screen coordinate.
    virtual void sync();

	virtual void snapCall(Point&, std::function<void(int, int)>);
};

}
