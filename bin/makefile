sources = $(shell ls  ./src/*.cpp)
objects = $(shell ls  ./*.o)

lib = -lSDL2 -lSDL2_image
Include = -I../include -I/usr/include/SDL2
CPPFLAGS= $(include) $(lib)
COMPILER = g++

all:setupsdl.o grid.o holaopengl.o circle.o
	$(COMPILER) -o ../release/terreno.out $(objects) $(lib)
setupsdl.o:../src/setupsdl.cpp ../include/setup.hpp
	$(COMPILER) -c ../src/setupsdl.cpp $(Include) 
grid.o:../src/grid.cpp ../include/grid.hpp
	$(COMPILER) -c ../src/grid.cpp $(Include) 
holaopengl.o:../src/holaopengl.cpp ../include/grid.hpp \
		   ../include/setup.hpp
	$(COMPILER) -c ../src/holaopengl.cpp $(Include)
circle.o:../src/circle.cpp ../include/grid.hpp \
		   ../include/setup.hpp
	$(COMPILER) -c ../src/circle.cpp $(Include)
clear:
	rm $(objects)
