CC=g++
CFLAGS=-Iinclude -std=c++11 -g
LIBS=-lfreeglut -lglew32 -lopengl32 -lglu32 # Windows
# LIBS=-lglut -lGLEW -lGL -lGLU # Linux

# Default target executed when no arguments are given to make.
default_target: main
.PHONY : default_target

main: main.o InitShader.o Objects.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

main.o: main.cc
	$(CC) $(CFLAGS) -c $^

InitShader.o: common/InitShader.cc
	$(CC) $(CFLAGS) -c $^

Objects.o: common/Objects.cc
	$(CC) $(CFLAGS) -c $^

clean:
#del /f /q main.exe *.o # Windows
	rm -f main *~ *.o Linux (or Mysus64)

