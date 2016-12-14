all: raytracer

raytracer: main.o img_writer.o scene.o sphere.o
	g++ main.o img_writer.o scene.o sphere.o -o raytracer

main.o: main.cpp
	g++ -c main.cpp

img_writer.o: img_writer.cpp
	g++ -c img_writer.cpp

scene.o: scene.cpp
	g++ -c scene.cpp

sphere.o: sphere.cpp
	g++ -c sphere.cpp
