#include "snakepair.h"

bool SnakePair::operator==(const SnakePair& another) const {
	if(x != another.x) return false;
	if(y != another.y) return false;
	return true;
}
