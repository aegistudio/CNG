#pragma once
namespace cng {

class Point {
public:
	int x, y;
	Point(int p_x, int p_y)
		: x(p_x), y(p_y) {}
};

class Dimension {
public:
	int width;
	int height;
	Dimension(int p_w, int p_h)
		: width(p_w), height(p_h) {}
};

struct Rect {
public:
	Point location;
	Dimension size;
	Rect(int x, int y, int w, int h)
		: location(x, y), size(w, h) {}
	Rect(Point p_l, Dimension p_sz)
		: location(p_l), size(p_sz) {}

	void confine(const Rect& another) {
		if(location.x < another.location.x)
			location.x = another.location.x;
		if(location.y < another.location.y)
			location.y = another.location.y;

		int maxAllowedX = another.location.x + another.size.width;
		if(location.x + size.width > maxAllowedX)
			size.width = maxAllowedX - location.x;

		int maxAllowedY = another.location.y + another.size.height;
		if(location.y + size.height > maxAllowedY)
			size.height = maxAllowedY - location.y;
	}

	Point upperLeft() {
		return Point(
			location.x + 0,
			location.y + 0);
	}

	Point upperRight() {
		return Point(
			location.x + size.width - 1,
			location.y + 0);
	}

	Point lowerLeft() {
		return Point(
			location.x + 0,
			location.y + size.height - 1);
	}

	Point lowerRight() {
		return Point(
			location.x + size.width  - 1,
			location.y + size.height - 1);
	}
};

} // End of namespace cng.
