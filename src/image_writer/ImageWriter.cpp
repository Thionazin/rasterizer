#include "ImageWriter.h"
#include "../Image.h"
#include "../triangle/Triangle.h"
#include <vector>
#include <iostream>
#include "float.h"
#include "math.h"


void ImageWriter::draw_bounding_boxes(Image &im, std::vector<Triangle*> &tri) {
	for(unsigned int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				im.setPixel(r, c, 255*RANDOM_COLORS[i%7][0], 255*RANDOM_COLORS[i%7][1], 255*RANDOM_COLORS[i%7][2]);
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
	}
}


void ImageWriter::draw_triangles(Image &im, std::vector<Triangle*> &tri) {
	for(unsigned int i = 0; i < tri.size(); i++) {
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
	for(unsigned int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				if(a >= 0 && b >= 0 && see >=0) {
					double red = (255*RANDOM_COLORS[counter%7][0])*a + (255*RANDOM_COLORS[(counter+1)%7][0])*b + (255*RANDOM_COLORS[(counter+2)%7][0])*see;
					double green = (255*RANDOM_COLORS[counter%7][1])*a + (255*RANDOM_COLORS[(counter+1)%7][1])*b + (255*RANDOM_COLORS[(counter+2)%7][1])*see;
					double blue = (255*RANDOM_COLORS[counter%7][2])*a + (255*RANDOM_COLORS[(counter+1)%7][2])*b + (255*RANDOM_COLORS[(counter+2)%7][2])*see;
					im.setPixel(r, c, red, green, blue);
				}
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
		counter+=3;
	}

}


void ImageWriter::vertical_color(Image& im, std::vector<Triangle*> &tri, double height, double base) {
	for(unsigned int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				if(a >= 0 && b >= 0 && see >=0) {
					im.setPixel(r, c, 255*((c-base)/height), 0, 255*(1-((c-base)/height)));
				}
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
	}
}

void ImageWriter::z_buffering(Image& im, std::vector<Triangle*> &tri, double z_range, double z_base, int width, int height) {
	double** z_buff = new double*[height];
	for(int i = 0; i < height; i++) {
		z_buff[i] = new double[width];
		for(int j = 0; j < width; j++) {
			z_buff[i][j] = -DBL_MAX;
		}
	}
	for(unsigned int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				double z_coord = a*tri[i]->get_v1().z + b*tri[i]->get_v2().z + see*tri[i]->get_v3().z;
				if(z_coord > z_buff[r][c] && a >= 0 && b >= 0 && see >=0) {
					im.setPixel(r, c, 255*((z_coord-z_base)/z_range), 0, 0);
					z_buff[r][c] = z_coord;
				}
				//im.setPixel(r, c, 0, 255, 0);
			}
		}
	}
	for(int i = 0; i < height; i++) {
		delete[] z_buff[i];
	}
	delete[] z_buff;
}


void ImageWriter::normal_coloring(Image& im, std::vector<Triangle*> &tri, double z_range, double z_base, int width, int height) {
	double** z_buff = new double*[height];
	for(int i = 0; i < height; i++) {
		z_buff[i] = new double[width];
		for(int j = 0; j < width; j++) {
			z_buff[i][j] = -DBL_MAX;
		}
	}
	for(unsigned int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				double z_coord = a*tri[i]->get_v1().z + b*tri[i]->get_v2().z + see*tri[i]->get_v3().z;
				if(z_coord > z_buff[r][c] && a >= 0 && b >= 0 && see >=0) {
					double n_x = a*tri[i]->get_v1().nx + b*tri[i]->get_v2().nx + see*tri[i]->get_v3().nx;
					double n_y = a*tri[i]->get_v1().ny + b*tri[i]->get_v2().ny + see*tri[i]->get_v3().ny;
					double n_z = a*tri[i]->get_v1().nz + b*tri[i]->get_v2().nz + see*tri[i]->get_v3().nz;
					im.setPixel(r, c, 255*(0.5*n_x+0.5), 255*(0.5*n_y+0.5), 255*(0.5*n_z+0.5));
					z_buff[r][c] = z_coord;
				}
			}
		}
	}
	for(int i = 0; i < height; i++) {
		delete[] z_buff[i];
	}
	delete[] z_buff;
}

void ImageWriter::lighting(Image& im, std::vector<Triangle*> &tri, double z_range, double z_base, int width, int height) {
	double** z_buff = new double*[height];
	for(int i = 0; i < height; i++) {
		z_buff[i] = new double[width];
		for(int j = 0; j < width; j++) {
			z_buff[i][j] = -DBL_MAX;
		}
	}
	for(unsigned int i = 0; i < tri.size(); i++) {
		for(int r = tri[i]->minX(); r < tri[i]->maxX(); r++) {
			for(int c = tri[i]->minY(); c < tri[i]->maxY(); c++) {
				double area = tri[i]->area();
				Vertex p(r, c, 0);
				double a = tri[i]->area_a(p) / area;
				double b = tri[i]->area_b(p) / area;
				double see = tri[i]->area_c(p) / area;
				double z_coord = a*tri[i]->get_v1().z + b*tri[i]->get_v2().z + see*tri[i]->get_v3().z;
				if(z_coord > z_buff[r][c] && a >= 0 && b >= 0 && see >=0) {
					double n_x = a*tri[i]->get_v1().nx + b*tri[i]->get_v2().nx + see*tri[i]->get_v3().nx;
					double n_y = a*tri[i]->get_v1().ny + b*tri[i]->get_v2().ny + see*tri[i]->get_v3().ny;
					double n_z = a*tri[i]->get_v1().nz + b*tri[i]->get_v2().nz + see*tri[i]->get_v3().nz;
					double dot = (1/sqrt(3))*n_x + (1/sqrt(3))*n_y + (1/sqrt(3))*n_z;
					double scalar = std::max(dot, 0.0);
					im.setPixel(r, c, scalar*255, scalar*255, scalar*255);
					z_buff[r][c] = z_coord;
				}
			}
		}
	}
	for(int i = 0; i < height; i++) {
		delete[] z_buff[i];
	}
	delete[] z_buff;
}

