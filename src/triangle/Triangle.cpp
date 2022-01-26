#include "Triangle.h"
#include <algorithm>

void Triangle::scale_vertices(double scale, double offset_x, double offset_y) {
	v1.x = scale*v1.x + offset_x;
	v2.x = scale*v2.x + offset_x;
	v3.x = scale*v3.x + offset_x;
	v1.y = scale*v1.y + offset_y;
	v2.y = scale*v2.y + offset_y;
	v3.y = scale*v3.y + offset_y;
}

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

double Triangle::maxZ() {
	return std::max({v1.z, v2.z, v3.z});
}

double Triangle::minZ() {
	return std::min({v1.z, v2.z, v3.z});
}

double Triangle::area() {
	return 0.5*((v2.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (v2.y - v1.y));
}

double Triangle::area_a(Vertex p) {
	return 0.5*((v2.x - p.x) * (v3.y - p.y) - (v3.x - p.x) * (v2.y - p.y));
}

double Triangle::area_b(Vertex p) {
	return 0.5*((v3.x - p.x) * (v1.y - p.y) - (v1.x - p.x) * (v3.y - p.y));
}

double Triangle::area_c(Vertex p) {
	return 0.5*((v1.x - p.x) * (v2.y - p.y) - (v2.x - p.x) * (v1.y - p.y));
}
