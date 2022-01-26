#include "ImageWriter.h"
#include "../Image.h"
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
