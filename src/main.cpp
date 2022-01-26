#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "triangle/Triangle.h"
#include "image_writer/ImageWriter.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char **argv)
{
	if(argc < 6) {
		cout << "Usage: A1 meshfile output width height task_number" << endl;
		return 0;
	}
	// Parameters loaded in the variables
	string meshName(argv[1]);
	string output(argv[2]);
	double width = atof(argv[3]);
	double height = atof(argv[4]);
	int task = atoi(argv[5]);

	//initialize image object
	Image image(width, height);


	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
					if(!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;

	// vector of triangles
	vector<Triangle*> tri_list;

	// image writer
	ImageWriter iw;

	// max and min x and y, to be used for scaling
	double maxX = posBuf[0];
	double maxY = posBuf[1];
	double minX = posBuf[0];
	double minY = posBuf[1];


	// process triangles in the vector into a vector of triangle objects
	int i = 0;
	while(i < posBuf.size()) {
		Vertex v1(posBuf[i], posBuf[i+1], posBuf[i+2]);
		Vertex v2(posBuf[i+3], posBuf[i+4], posBuf[i+5]);
		Vertex v3(posBuf[i+6], posBuf[i+7], posBuf[i+8]);
		Triangle* tri = new Triangle(v1, v2, v3);
		tri_list.push_back(tri);
		maxX = max(maxX, tri->maxX());
		maxY = max(maxY, tri->maxY());
		minX = min(minX, tri->minX());
		minY = min(minY, tri->minY());
		i += 9;
	}




	// determine the limiting factor and scale
	double scale = 0;
	if((maxX - minX) > (maxY - minY)) {
		// height
		scale = height / (maxX - minX);
	} else {
		// width
		scale = width / (maxY - minY);
	}

	// coordinates of the origin used for scaling
	double origin_x = 0.5*(minX + maxX);
	double origin_y = 0.5*(minY + maxY);




	// determine offset
	double offset_x = width/2 - scale*origin_x;
	double offset_y = height/2 - scale*origin_y;


	cout << "scale: " << scale << endl;
	cout << "+x: " << offset_x << endl;
	cout << "+y: " << offset_y << endl;


	// scales the vertices in the vector
	for(int i = 0; i < tri_list.size(); i++) {
		tri_list[i]->scale_vertices(scale, offset_x, offset_y);
	}




	// sends the image as well as the parameter to process the file
	switch(task) {
		case 1:
			iw.draw_bounding_boxes(image, tri_list);
			break;
		default:
			cout << "failure" << endl;
	}



	// cleares the heap memory
	
	for(int i = 0; i < tri_list.size(); i++) {
		delete tri_list[i];
	}

	// writes the image to the specified output file name
	image.writeToFile(output);
	return 0;
}
