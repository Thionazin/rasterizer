#include "Triangle.h"
#include <algorithm>

double Triangle::maxX() {
	return std::max({v1.x, v2.x, v3.x});
}

double Triangle::maxY() {
	return std::max({v1.y, v2.y, v3.y});
}

double Triangle::minX() {
	return std::min({v1.x, v2.x, v3.x});
}

double Triangle::minY() {
	return std::min({v1.y, v2.y, v3.y});
}
