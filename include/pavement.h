#include <Angel.h>
#include "Object.h"

#ifndef PAVEMENT_H
#define PAVEMENT_H

class Pavement : public Object {
 public:
    Pavement(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    ~Pavement();
    void draw() const;
    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();
 private:
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[1], buffer[1];
};

#endif