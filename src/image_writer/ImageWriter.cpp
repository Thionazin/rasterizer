#include "ImageWriter.h"
#include "../Image.h"
#include "../triangle/Triangle.h"
#include <vector>
#include <iostream>


void ImageWriter::draw_bounding_boxes(Image &im, std::vector<Triangle*> &tri) {
	for(int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				im.setPixel(r, c, 255*RANDOM_COLORS[i%7][0], 255*RANDOM_COLORS[i%7][1], 255*RANDOM_COLORS[i%7][2]);
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
	}
}


void ImageWriter::draw_triangles(Image &im, std::vector<Triangle*> &tri) {
	for(int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				if(a >= 0 && b >= 0 && see >=0) {
					im.setPixel(r, c, 255*RANDOM_COLORS[i%7][0], 255*RANDOM_COLORS[i%7][1], 255*RANDOM_COLORS[i%7][2]);
				}
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
	}
}


void ImageWriter::interpolate_colors(Image& im, std::vector<Triangle*> &tri) {
	int counter = 0;
	for(int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				double red = (255*RANDOM_COLORS[counter%7][0])*a + (255*RANDOM_COLORS[(counter+1)%7][0])*b + (255*RANDOM_COLORS[(counter+2)%7][0])*see;
				double green = (255*RANDOM_COLORS[counter%7][1])*a + (255*RANDOM_COLORS[(counter+1)%7][1])*b + (255*RANDOM_COLORS[(counter+2)%7][1])*see;
				double blue = (255*RANDOM_COLORS[counter%7][2])*a + (255*RANDOM_COLORS[(counter+1)%7][2])*b + (255*RANDOM_COLORS[(counter+2)%7][2])*see;
				if(a >= 0 && b >= 0 && see >=0) {
					im.setPixel(r, c, red, green, blue);
				}
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
		counter+=3;
	}

}
