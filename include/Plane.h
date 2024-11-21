#include <Angel.h>

#ifndef PLANE_H
#define PLANE_H

using namespace std;

class Plane {
 public:
    Plane(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    ~Plane();
    void draw() const;
 private:
  GLuint vao[1], buffer[1];
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
 
};

#endif