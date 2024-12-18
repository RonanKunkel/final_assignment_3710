CC=g++
CFLAGS=-Iinclude -std=c++11 -g
LIBS=-lfreeglut -lglew32 -lopengl32 -lglu32 # Windows
# LIBS=-lglut -lGLEW -lGL -lGLU # Linux

# Default target executed when no arguments are given to make.
default_target: main
.PHONY : default_target

main: main.o InitShader.o Object.o Plane.o Car.o Camera.o Buildings.o Pavement.o Wheels.o light.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: main.cc
	$(CC) $(CFLAGS) -c $^

InitShader.o: common/InitShader.cc
	$(CC) $(CFLAGS) -c $^

Object.o: common/Object.cc
	$(CC) $(CFLAGS) -c $^

Plane.o: common/Plane.cc
	$(CC) $(CFLAGS) -c $^

Car.o: common/Car.cc
	$(CC) $(CFLAGS) -c $^

Camera.o: common/Camera.cc
	$(CC) $(CFLAGS) -c $^

Pavement.o: common/Pavement.cc
	$(CC) $(CFLAGS) -c $^

Buildings.o: common/Buildings.cc
	$(CC) $(CFLAGS) -c $^
Wheels.o: common/Wheels.cc
	$(CC) $(CFLAGS) -c $^

light.o: common/light.cc
	$(CC) $(CFLAGS) -c $^

clean:
#del /f /q main.exe *.o # Windows
	rm -f main *~ *.o

