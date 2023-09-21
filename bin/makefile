sources = $(shell ls  ./src/*.cpp)
objects = $(shell ls  ./*.o)

lib = -lSDL2 -lSDL2_image
Include = -I../include
CPPFLAGS= $(include) $(lib)
all:setupsdl.o grid.o holaopengl.o circle.o
	g++ -o ../release/terreno.out $(objects) $(lib)
setupsdl.o:../src/setupsdl.cpp ../include/setup.hpp
	g++ -c ../src/setupsdl.cpp $(Include) 
grid.o:../src/grid.cpp ../include/grid.hpp
	g++ -c ../src/grid.cpp $(Include) 
holaopengl.o:../src/holaopengl.cpp ../include/grid.hpp \
		   ../include/setup.hpp
	g++ -c ../src/holaopengl.cpp $(Include)
circle.o:../src/circle.cpp ../include/grid.hpp \
		   ../include/setup.hpp
	g++ -c ../src/circle.cpp $(Include) 
clear:
	rm $(objects)
