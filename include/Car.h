#include <Angel.h>
#include "Object.h"

#ifndef CAR_H
#define CAR_H

using namespace std;

class Car : public Object {
 public:
    Car(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 0.02, GLfloat scale_y = 0.02, GLfloat scale_z = 0.02);

    ~Car();

    vec4 getPosition() const;

    void draw() const;

    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
    GLuint vao[10], buffer[10];
};

#endif