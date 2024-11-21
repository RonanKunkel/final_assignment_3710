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

main: main.o InitShader.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: main.cc
	$(CC) $(CFLAGS) -c $^

InitShader.o: common/InitShader.cc
	$(CC) $(CFLAGS) -c $^

clean:
ifeq ($(OS),Windows_NT)
	del /f /q main.exe *.o
else
	rm -f main *~ *.o
endif
