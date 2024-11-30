#include <Angel.h>
#include "Object.h"
#include "Plane.h"

#ifndef BUILDINGS_H
#define BUILDINGS_H

using namespace std;
// building 1 constructor: 
// takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
// scale factor for x,y,z coordinates and theta( rotation angle ) for x,y,z coordinates and starting position( pos ).
class building1 : public Object { // Maksym
 public:
  building1(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  // building 1 destructor
  ~building1();
  // building one draw function: draws each face of the object.
  void draw() const;
//movement functions
//moveLeft: rotates object right, updates current direction.
//moveRight: rotates object left, updates current direction.
//moveForward translates object backwards depending on current direcion
//moveBackwards translates object forwards. depending on current direcion 
  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackward();
  //initializing enum to keep track of directions for movement functions.
  enum direction {north,east, south, west};
  direction currentdirection;
  //initializing model 
  mat4 model;
//initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[10], buffer[10];
};


class building2 : public Object { // Desmond
 public:
// building 2 constructor: 
// takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
// scale factor for x,y,z coordinates and theta( rotation angle ) for x,y,z coordinates and starting position( pos ).
  building2(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  // building  destructor
  ~building2();
  // building draw function: draws each face of the object.
  void draw() const;
//movement functions
//moveLeft: rotates object right, updates current direction.
//moveRight: rotates object left, updates current direction.
//moveForward translates object backwards depending on current direcion
//moveBackwards translates object forwards. depending on current direcion
  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackward();
//initializing enum to keep track of directions for movement functions.
  enum direction {north, east, south, west};
  direction currentdirection;
  //initializing model 
  mat4 model;
  //initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[11], buffer[11];
};
class building3 : public Object { // Albert
 public:
 // building 3 constructor: 
 // takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
 // scale factor for x,y,z coordinates and theta( rotation angle ) for x,y,z coordinates and starting position( pos ).
    building3(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  //building  destructor
    ~building3();
  //building draw function: draws each face of the object.
    void draw() const;
//movement functions
//moveLeft: rotates object right, updates current direction.
//moveRight: rotates object left, updates current direction.
//moveForward translates object backwards depending on current direcion
//moveBackwards translates object forwards. depending on current direcion
    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();
//initializing enum to keep track of directions for movement functions.
      enum direction {north,east, south, west};
      direction currentdirection;
//initializing model 
  mat4 model;
//initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[13], buffer[13];
};
class building4 : public Object { // Ronan
 public:
// building 4 constructor: 
// takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
// scale factor for x,y,z coordinates and theta( rotation angle ) for x,y,z coordinates and starting position( pos ).
  building4(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  //building  destructor
  ~building4();
  //building draw function: draws each face of the object.
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
//initializing enum to keep track of directions for movement functions.
  enum direction {north,east, south, west};
  direction currentdirection;
//initializing model 
  mat4 model;
//initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[16], buffer[16];

};
class building5 : public Object { // Free-For-All
 public:
// building 5 constructor: 
// takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
// scale factor for x,y,z coordinates and theta( rotation angle ) for x,y,z coordinates and starting position( pos ).
    building5(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  //building  destructor
    ~building5();
  //building draw function: draws each face of the object.  
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
//initializing enum to keep track of directions for movement functions.
 enum direction {north,east, south, west};
 direction currentdirection;
//initializing model 
  mat4 model;
//initializing vertex location, face location and model location variables
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[10], buffer[10];
};


#endif