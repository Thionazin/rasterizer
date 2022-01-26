#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

struct Vertex {
	double x;
	double y;
	double z;
	Vertex(double x, double y, double z) : x(x), y(y), z(z) {}
};

class Triangle
{
	public:
		Triangle(Vertex v1, Vertex v2, Vertex v3) : v1(v1), v2(v2), v3(v3) {};
		void scale_vertices(double scale, double offset_x, double offset_y);
		double maxX();
		double maxY();
		double maxZ();
		double minX();
		double minY();
		double minZ();

	private:
		Vertex v1;
		Vertex v2;
		Vertex v3;

};

#endif
