#include <Angel.h>

#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

class Light
{
public:
// traffic light constructor: 
// takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
// scale factor for x,y,z coordinates and theta( rotation angle ) for x,y,z coordinates and starting position( pos ).
  Light(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc,
	vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0, GLfloat theta_z = 0,
	GLfloat scale_x = 1, GLfloat scale_y = 1, GLfloat scale_z = 1);
  ~Light();


// function for colour incrementation.
  void next_colour();
// function for drawing objects of traffic light.
  void draw() const;
// movement functions
//moveLeft: rotates object right, updates current direction.
//moveRight: rotates object left, updates current direction.
//moveForward translates object backwards depending on current direcion
//moveBackwards translates object forwards. depending on current direcion
  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackward();


private:
//initializing enum to keep track of directions for movement functions.
 enum direction {north,east, south, west};
 direction currentdirection;

// creating 2 vertex array objects and buffers: one for the trafficlight shell, second for trafficlight colour changing object.
  GLuint vao[2], buffer[2], ebo[10];
 
  //initializing model, colour index, vertex location, face location, model location variables.
  mat4 model;
  int color_index;
  GLuint vertex_loc, face_loc, model_loc;
};

#endif
