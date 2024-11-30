#include <Angel.h>
#include "Object.h"

#ifndef CAR_H
#define CAR_H

using namespace std;

class Car : public Object {
 public:
    // Constructor for car
    Car(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
    GLfloat scale_x, GLfloat scale_y, GLfloat scale_z);

    // Deconstructor for car
    ~Car();

    // Function to get current car position for use in camera
    vec4 getPosition() const;

    // Draw funciton for the car
    void draw() const;

    // Initializing locs, vaos, ans buffers for the car
    mat4 model;
    GLuint vertex_loc, face_loc, model_loc;
    GLuint vao[102], buffer[102];
};

#endif