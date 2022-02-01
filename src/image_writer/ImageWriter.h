#pragma once

#include <vector>
#include "../Image.h"
#include "../triangle/Triangle.h"

class ImageWriter
{
	public:
		void draw_bounding_boxes(Image& im, std::vector<Triangle*> &tri);
		void draw_triangles(Image& im, std::vector<Triangle*> &tri);
		void interpolate_colors(Image& im, std::vector<Triangle*> &tri);
		void vertical_color(Image& im, std::vector<Triangle*> &tri, double height, double base);
		void z_buffering(Image& im, std::vector<Triangle*> &tri, double z_range, double z_base, int width, int height);
		void normal_coloring(Image& im, std::vector<Triangle*> &tri, double z_range, double z_base, int width, int height);
		void lighting(Image& im, std::vector<Triangle*> &tri, double z_range, double z_base, int width, int height);
	private:
		double RANDOM_COLORS[7][3] = {
			{0.0000,    0.4470,    0.7410},
			{0.8500,    0.3250,    0.0980},
			{0.9290,    0.6940,    0.1250},
			{0.4940,    0.1840,    0.5560},
			{0.4660,    0.6740,    0.1880},
			{0.3010,    0.7450,    0.9330},
			{0.6350,    0.0780,    0.1840},
		};
};
