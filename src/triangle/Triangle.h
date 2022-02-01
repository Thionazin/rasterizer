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
		double area();
		double area_a(Vertex p);
		double area_b(Vertex p);
		double area_c(Vertex p);
		double maxX();
		double maxY();
		double maxZ();
		double minX();
		double minY();
		double minZ();
        Vertex get_v1() { return v1; }
        Vertex get_v2() { return v2; }
        Vertex get_v3() { return v3; }

	private:
		Vertex v1;
		Vertex v2;
		Vertex v3;

};

#endif
