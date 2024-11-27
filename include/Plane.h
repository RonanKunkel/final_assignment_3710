#include <Angel.h>
#include "Object.h"

#ifndef PLANE_H
#define PLANE_H

class Plane : public Object {
 public:
    Plane(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    ~Plane();
    void draw() const;
    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();
   //  direction getDirection();

    vec4 currentPosition;
 private:
 enum direction {north,east, south, west};
 direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[1], buffer[1];
};

#endif