#include "Pavement.h"

// PavementX constructor 
//Takes in vertex location, face location, model location 
// scales factor for x,y,z, rotation of x,y,z and postion
PavementX::PavementX(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
  // vertex defintions 
    const vec4 point[4] = {
      vec4(-0.25, 0.0001, 7.25, 1), //v0
      vec4(0.25, 0.0001, 7.25, 1),  //v1
      vec4(-0.25, 0.0001, -7.25, 1), //v2
      vec4(0.25, 0.0001, -7.25, 1) //v3
    };
  //face defintions 
    const int face[1][4] = {
      {0,1,3,2}
    };
    // generating amount of vaos and buffers 
    glGenVertexArrays(1, vao);
    glGenBuffers(1, buffer);
    // to pass buffer data
    for (int i = 0; i < 1; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
      // add points to face 
      vec4 A[4];
      int size = 0;
      for (int j = 0; j < 4; j++) {
        if (face[i][j] >= 0) {
	        A[size++] = point[face[i][j]];
        }
      }
        //passing buffer data 
      glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }
    //model calculation
    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}
//PavementX deconstructor 
PavementX::~PavementX()
{
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, buffer);
}
//draw function using triangle fan 
void PavementX::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
  glBindVertexArray(vao[0]);
  glUniform4fv(face_loc, 1, vec4(0.4,0.4,0.4,1));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[0]);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);


  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
// movement functions: 
//turns left and rotates it -90 degrees and updates current location
void PavementX::moveLeft() {
    model =  RotateY(-90) * model;
    currentdirection = static_cast<direction>((currentdirection + 3) % 4);
    }

//turns right and rotates it 90 degrees and updates current location
void PavementX::moveRight() {
    model = RotateY(90) * model;
    currentdirection = static_cast<direction>((currentdirection + 1) % 4);
    }
// translates object backwards in current direction
void PavementX::moveForward() {
  switch(currentdirection){
    case north: 
      model = model * Translate(0.0, 0, 0.5);
      break;
    case east: 
      model = model * Translate(-0.5, 0.0, 0.0);
      break;
    case south: 
      model = model * Translate(0.0, 0.0, -0.5);
      break;
    case west: 
      model = model * Translate(0.5, 0.0, 0.0);
      break;
  }}
// translates object backwards in current direction
void PavementX::moveBackward() {
  switch(currentdirection){
    case north: 
      model = model * Translate(0.0, 0.0, -0.5); 
      break;
    case east: 
      model = model * Translate(0.5, 0.0, 0.0);
      break;
    case south: 
      model = model * Translate(0.0, 0.0, 0.5);
      break;
    case west: 
      model = model * Translate(-0.5, 0.0, 0.0);
      break;
  }}

// PavementZ constructor 
//Takes in vertex location, face location, model location 
// scales factor for x,y,z, rotation of x,y,z and postion
PavementZ::PavementZ(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
  // vertex defintions 
    const vec4 point[4] = {

      vec4(7.25, 0.0001, -0.25, 1), //v0
      vec4(7.25, 0.0001, 0.25, 1),  //v1
      vec4(-7.25, 0.0001, -0.25, 1), //v2
      vec4(-7.25, 0.0001, 0.25, 1) //v3

    };
  //face defintions 
    const int face[1][4] = {
      {0,1,3,2}
    };
    glGenVertexArrays(1, vao);
    glGenBuffers(1, buffer);
    // to pass buffer data
    for (int i = 0; i < 1; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);

      // add points to face 
      vec4 A[4];
      int size = 0;
      for (int j = 0; j < 4; j++) {
        if (face[i][j] >= 0) {
	        A[size++] = point[face[i][j]];
        }
      }
      //passing buffer data 
      glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }
    //model calculation
    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}
//PavementZ deconstructor 
PavementZ::~PavementZ()
{
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, buffer);
}
//draw function using triangle fan 
void PavementZ::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

  glBindVertexArray(vao[0]);
  glUniform4fv(face_loc, 1, vec4(0.4,0.4,0.4,1));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[0]);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);


  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
// movement functions: 
//turns left and rotates it -90 degrees and updates current location
void PavementZ::moveLeft() {
    model = RotateY(-90) * model;
    currentdirection = static_cast<direction>((currentdirection + 3) % 4);
    }
//turns right and rotates it 90 degrees and updates current location
void PavementZ::moveRight() {
    model =  RotateY(90) * model;
    currentdirection = static_cast<direction>((currentdirection + 1) % 4);
    }
// translates object backwards in current direction
void PavementZ::moveForward() {
  switch(currentdirection){
    case north: 
      model = model * Translate(0.0, 0, 0.5);
      break;
    case east: 
      model = model * Translate(-0.5, 0.0, 0.0);
      break;
    case south: 
      model = model * Translate(0.0, 0.0, -0.5);
      break;
    case west: 
      model = model * Translate(0.5, 0.0, 0.0);
      break;
  }}
// translates object backwards in current direction
void PavementZ::moveBackward() {
  switch(currentdirection){
    case north: 
      model = model * Translate(0.0, 0.0, -0.5); 
      break;
    case east: 
      model = model * Translate(0.5, 0.0, 0.0);
      break;
    case south: 
      model = model * Translate(0.0, 0.0, 0.5);
      break;
    case west: 
      model = model * Translate(-0.5, 0.0, 0.0);
      break;
  }}
