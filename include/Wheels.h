#include <Angel.h>
#include "Object.h"
#include "Plane.h"

#ifndef WHEELS_H
#define WHEELS_H

using namespace std;

class Wheels : public Object {
 public:
    Wheels(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    ~Wheels();
    void draw() const;
    void moveForward();
    void moveBackward();
    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
    GLuint vao[39], buffer[39];
};

#endif