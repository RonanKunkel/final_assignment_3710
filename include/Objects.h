/*   
*/

#include <Angel.h>

#ifndef OBJECTS_H
#define OBJECTS_H

using namespace std;

class Object {
//  public:
//     Object(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
//     vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
//     GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
//     ~Object();
//     void draw() const;
//  private:
//   mat4 model;
//   GLuint vertex_loc, face_loc, model_loc;

};

class Plane : public Object {
 public:
    Plane(GLuint vertexloc, GLuint faceloc, GLuint modeloc,
    vec4 pos, GLfloat theta_x = 0, GLfloat theta_y = 0,GLfloat theta_z = 0,
    GLfloat scale_x = 1,GLfloat scale_y = 1,GLfloat scale_z = 1);
    ~Plane();
    void draw() const;
 private:
  mat4 model;
  GLuint vertex_loc, face_loc, model_loc;
  GLuint vao[1], buffer[1];
};

class building1 : public Object { // Maksym
 public:

 private:
   GLuint vao[1], buffer[1];


};
class building2 : public Object { // Desmond
   public:

   private:
   GLuint vao[1], buffer[1];



};
class building3 : public Object { // Albert
   public:

   private:
   GLuint vao[1], buffer[1];




};
class building4 : public Object { // Ronan
   public:

   private:
   GLuint vao[1], buffer[1];




};
class building5 : public Object { // Free-For-All
   public:

   private:
   GLuint vao[1], buffer[1];



};

class trafficLight : public Object {
   public:

   private:
   GLuint vao[1], buffer[1];
};

#endif