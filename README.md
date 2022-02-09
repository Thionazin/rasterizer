# Usage

To build:

Make a new directory called build inside the project folder and enter it.

Generate makefiles by using the command
```
cmake ..
```

Make the project with
```
make -j4
```
-j4 is optional

Run with the format:
```
./A1 <path to obj> <output file name> <width> <height> <task number>
```

# Tasks

1. Draw bounding boxes with random colors
2. Draw triangles with random colors
3. Draw triangles with colors interpolated from each vertex
4. Draw object with color linearly interpolated from the y coordinate
5. Draw object with z buffering
6. Draw object with normal map
7. Draw object with basic lighting in the top right corner.

# Credits

The mesh loader is an obj loader from http://github.com/syoyo/tinyobjloader, and the image writer is from http://github.com/nothings/stb.

Credits to Dr. Shinjiro Sueda for setting up the skeleton code.
