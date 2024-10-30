CC=g++
CFLAGS=-Iinclude -std=c++11 -g
ifeq ($(OS),Windows_NT)
	LIBS=-lfreeglut -lglew32 -lopengl32 -lglu32
else
	LIBS=-lglut -lGLEW -lGL -lGLU
endif
# Default target executed when no arguments are given to make.
default_target: main
.PHONY : default_target

main: main.o InitShader.o Buildings.o Camera.o Car.o City.o Traffic_Light.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: src/project/main.cc
	$(CC) $(CFLAGS) -c $^

InitShader.o: src/InitShader.cc
	$(CC) $(CFLAGS) -c $^

Buildings.o: src/Buildings.cc
	$(CC) $(CFLAGS) -c $^

Camera.o: src/Camera.cc
	$(CC) $(CFLAGS) -c $^

Car.o: src/Car.cc
	$(CC) $(CFLAGS) -c $^

City.o: src/City.cc
	$(CC) $(CFLAGS) -c $^

Traffic_Light.o: src/Traffic_Light.cc
	$(CC) $(CFLAGS) -c $^

clean:
ifeq ($(OS),Windows_NT)
	del /f /q main.exe *.o
else
	rm -f main *~ *.o
endif
