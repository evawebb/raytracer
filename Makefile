all: raytracer

raytracer: main.o img_writer.o scene.o sphere.o plane.o triangle.o texture.o
	g++ main.o img_writer.o scene.o sphere.o plane.o triangle.o texture.o -o raytracer

main.o: main.cpp
	g++ -c -g main.cpp

img_writer.o: img_writer.cpp
	g++ -c -g img_writer.cpp

scene.o: scene.cpp
	g++ -c -g scene.cpp

sphere.o: sphere.cpp
	g++ -c -g sphere.cpp

plane.o: plane.cpp
	g++ -c -g plane.cpp

triangle.o: triangle.cpp
	g++ -c -g triangle.cpp

texture.o: texture.cpp
	g++ -c -g texture.cpp
