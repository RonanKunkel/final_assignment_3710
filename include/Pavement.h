#include <Angel.h>
#include "Object.h"

#ifndef PAVEMENT_H
#define PAVEMENT_H

//pavementX constructor 
//takes in vertex location. face location, model location 
//scale factor for x,y,z coordinates 
class PavementX : public Object {
 public:
    PavementX(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    //PavementX deconstructor 
    ~PavementX();
    //pavementX draw faces of pavement 
    void draw() const;
   //movement function to rotate object and update current direction 
    void moveLeft();
   //movement function to rotate object and update current direction 
    void moveRight();
    //translates objects dependent on current direction
    void moveForward();
    //translates objects dependent on current direction
    void moveBackward();
 private:
 //intializing enum to keep track of current direction
  enum direction {north,east, south, west};
  //initalizing current direction 
 direction currentdirection;
//initalizing model  
  mat4 model;
    //initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
    //initalizing the amount of  vao and buffer 
  GLuint vao[1], buffer[1];
};

//pavementY constructor 
//takes in vertex location. face location, model location 
//scale factor for x,y,z coordinates 
class PavementZ : public Object {
 public:
    PavementZ(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    //PavementY deconstructor 
    ~PavementZ();
    //pavementY draw faces of pavement 
    void draw() const;
   //movement function to rotate object and update current direction 
    void moveLeft();
   //movement function to rotate object and update current direction 
    void moveRight();
    //translates objects dependent on current direction
    void moveForward();
    //translates objects dependent on current direction
    void moveBackward();
 private:
   //intializing enum to keep track of current direction
  enum direction {north,east, south, west};
  //initalizing current direction 
 direction currentdirection;
   //initalizing model  
  mat4 model;
    //initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
    //initalizing the amount of  vao and buffer 
  GLuint vao[1], buffer[1];
};

#endif
