#include <Angel.h>
#include "Object.h"

#ifndef PLANE_H
#define PLANE_H

class Plane : public Object {
 public:
  // Constructor for plane keeping scale to 1 for every vertice
  Plane(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  ~Plane();
  // fucntion to draw the plane
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
  // function used to restrict the players movement to the roads only
  int getDirection();   
  // vec4 also used to restrict players movement to roads only 
  vec4 currentPosition;
 private:
  // variables used for creation and movment of the plane object
  enum direction {north,east, south, west};
  direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[1], buffer[1];
};

#endif