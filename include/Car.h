#include <Angel.h>
#include "Object.h"

#ifndef CAR_H
#define CAR_H

using namespace std;

class Car : public Object {
 public:
    Car(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
    GLfloat scale_x, GLfloat scale_y, GLfloat scale_z);

    ~Car();

    vec4 getPosition() const;

    void draw() const;

    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
    GLuint vao[102], buffer[102];
};

#endif