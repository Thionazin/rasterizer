#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

struct Vertex {
	double x;
	double y;
	// double z;
	Vertex(int x, int y) : x(x), y(y) {}
};

class Triangle
{
	public:
		Triangle(Vertex v1, Vertex v2, Vertex v3) : v1(v1), v2(v2), v3(v3) {};
		double maxX();
		double maxY();
		// double maxZ();
		double minX();
		double minY();
		// double minZ();

	private:
		Vertex v1;
		Vertex v2;
		Vertex v3;

};

#endif
