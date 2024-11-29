#include <Angel.h>
#include "Object.h"
#include "Plane.h"

#ifndef BUILDINGS_H
#define BUILDINGS_H

using namespace std;

class building1 : public Object { // Maksym
 public:
  building1(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  ~building1();
  void draw() const;
  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackward();
  enum direction {north,east, south, west};
  direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[10], buffer[10];
};


class building2 : public Object { // Desmond
 public:
  building2(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  ~building2();
  void draw() const;
  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackward();
  enum direction {north, east, south, west};
  direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[7], buffer[7];
};
class building3 : public Object { // Albert
 public:
  building3(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  ~building3();
  void draw() const;
  enum direction {north,east, south, west};
  direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[0], buffer[0];


};
class building4 : public Object { // Ronan
 public:
  building4(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  ~building4();
  void draw() const;
  void moveLeft();
  void moveRight();
  void moveForward();
  void moveBackward();
  enum direction {north,east, south, west};
  direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[16], buffer[16];

};
class building5 : public Object { // Free-For-All
 public:
  building5(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
  vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
  GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
  ~building5();
  void draw() const;
  enum direction {north,east, south, west};
  direction currentdirection;
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[0], buffer[0];
};

// Blank green plane
class building6 : public Object {
public:
 building6(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
 vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
 GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
 ~building6();
 void draw() const;
 enum direction {north,east, south, west};
 direction currentdirection;
 mat4 model;
 GLuint vertex_loc, face_loc, model_loc;
 GLuint vao[0], buffer[0];
};

#endif