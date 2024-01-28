objects = $(shell ls ./*.o)
Include = -I../include -I/usr/include/SDL2 
lib = -lSDL2 -lSDL2_image 
setupsdl.o:../src/setupsdl.cpp
	g++ -c ../src/setupsdl.cpp $(Include)
holaopengl.o:../src/holaopengl.cpp
	g++ -c ../src/holaopengl.cpp $(Include)
colision.o:../src/colision.cpp
	g++ -c ../src/colision.cpp $(Include)
chunck.o:../src/chunck.cpp
	g++ -c ../src/chunck.cpp $(Include)
grid.o:../src/grid.cpp
	g++ -c ../src/grid.cpp $(Include)
physics.o:../src/physics.cpp
	g++ -c ../src/physics.cpp $(Include)
circle.o:../src/circle.cpp
	g++ -c ../src/circle.cpp $(Include)
all:setupsdl.o holaopengl.o colision.o chunck.o grid.o physics.o circle.o 
	g++ -o ../release/Tryingsdl.out $(objects) $(lib)
clear:
	rm -r $(objects)
