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

# Credits

The mesh loader is an obj loader from http://github.com/syoyo/tinyobjloader, and the image writer is from http://github.com/nothings/stb.

Credits to Dr. Shinjiro Sueda for setting up the skeleton code.
