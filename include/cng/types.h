#pragma once
namespace cng {

struct Point {
	int x, y;
};

struct Dimension {
	int width;
	int height;
};

struct Rect {
	Point location;
	Dimension size;
};

} // End of namespace cng.
