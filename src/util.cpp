#include "cng/util.h"
using namespace cng;

void cng::box(Graphics& graphics, Rect& boxRect,
	int horizontalLine, int verticalLine,
	int upperLeftCorner, int upperRightCorner,
	int lowerLeftCorner, int lowerRightCorner) {

	Dimension boxRectSize = boxRect.size;
	Point upperLeft  = boxRect.upperLeft();
	Point upperRight = boxRect.upperRight();
	Point lowerLeft  = boxRect.lowerLeft();
	Point lowerRight = boxRect.lowerRight();

    graphics.rowRepeat(upperLeft,
		boxRectSize.width, horizontalLine);

	graphics.rowRepeat(lowerLeft,
		boxRectSize.width, horizontalLine);

	graphics.columnRepeat(upperLeft,
		boxRectSize.height, verticalLine);

	graphics.columnRepeat(upperRight,
		boxRectSize.height, verticalLine);

	graphics.put(upperLeft,  upperLeftCorner);
	graphics.put(upperRight, upperRightCorner);
	graphics.put(lowerLeft,  lowerLeftCorner);
	graphics.put(lowerRight, lowerRightCorner);
}

void cng::center(Graphics& graphics, Point& point,
	int length, const char* text) {

	Point leftPoint = {point.x - length / 2, point.y};
    graphics.print(leftPoint, length, text);
}

Rect cng::center(Rect& source, Dimension& size) {
    Point startPoint = {
		source.location.x + (source.size.width - size.width) / 2,
		source.location.y + (source.size.height - size.height) / 2};
	Rect result = {startPoint, size};
	result.confine(source);
	return result;
}
