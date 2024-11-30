#include <Angel.h>
#include "Object.h"
#include "Plane.h"

#ifndef WHEELS_H
#define WHEELS_H

using namespace std;
//Wheel constructor 
//takes in: vertex location, face location, model location
//scale factor for x,y,z coordinates and rotation values as well as pos 
class Wheels : public Object {
 public:
    Wheels(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    //wheels deconstructor 
    ~Wheels();
    //wheel draw function 
    void draw() const;
    //move forward function rotates object 
    void moveForward();
    //move backward function rotates object 
    void moveBackward();
    //iniatlizing model 
    mat4 model;
    ////initializing vertex location, face location and model location variables
    GLuint vertex_loc, face_loc, model_loc;
    //initalizing the amount of  vao and buffer 
    GLuint vao[39], buffer[39];
};

#endif