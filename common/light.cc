#include "light.h"

Light::Light(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : color_index{0}, vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
  const vec4 point[12] =
    { vec4(-0.05, 0.3, -0.05, 1.0), //v0
    vec4(0.05, 0.3, -0.05, 1.0), //v1
      vec4(0.05, 0.3, 0.05, 1.0), //v2
      vec4(-0.05, 0.3, 0.05, 1.0),//v3

      vec4(-0.15, 0.4, -0.05, 1.0), //v4
      vec4(0.15, 0.4, -0.05, 1.0),//v5
      vec4(0.15, 0.4, 0.05, 1.0),  //v6
      vec4(-0.15, 0.4, 0.05, 1.0), //v7

      vec4(-0.05, 0.0, -0.05, 1.0), //v8
      vec4(0.05, 0.0, -0.05, 1.0),//v9
      vec4(0.05, 0.0, 0.05, 1.0),//v10
      vec4(-0.05, 0.0, 0.05, 1.0),//v11
    };

  const GLuint face[10][4] =
    {
     {0,1,2,3},  // bot
     {4,5,6,7},  // top
     {0,1,5,4},  // back
     {2,3,7,6},  // front
     {2,6,5,1},  // left
     {0,4,7,3},   // right

     {8,9,0,1}, // back
     {11,10,2,3}, //front
     {8,11,3,0}, //left
     {9,10,2,1} //right
    };
  
  glGenVertexArrays(2, vao);
  glGenBuffers(2, buffer);

  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			  BUFFER_OFFSET(0));

  glGenBuffers(10, ebo);
  for (int i = 0; i < 10; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }

  glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
  vec4 A[8] =
    {
     vec4(-0.05, 0.38, 0.051, 1),  vec4(0.05, 0.38, 0.051, 1),
     vec4(0.05, 0.32, 0.051, 1),
     vec4(-0.05, 0.32, 0.051, 1),

    vec4(-0.05, 0.38, 0.051, 1),  vec4(0.05, 0.38, 0.051, 1),
     vec4(0.05, 0.32, 0.051, 1),
     vec4(-0.05, 0.32, 0.051, 1)
    };



  glBufferData(GL_ARRAY_BUFFER, sizeof(A), A, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

  model = Translate(pos)
    * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
    * Scale(scale_x, scale_y, scale_z);
}

Light::~Light()
{
  glDeleteVertexArrays(2, vao);
  glDeleteBuffers(2, buffer);
  glDeleteBuffers(10, ebo);
}

void Light::next_colour()
{
  color_index = (color_index + 1) % 3;
}

void Light::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

  glBindVertexArray(vao[0]);
  for (int i = 0; i < 10; i++) {
    GLfloat v = 0.75 * (i+1)/6.0;
    glUniform4fv(face_loc, 1, vec4(0.4, 0.4, 0.0, 1.0));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  }

  vec4 lightColor[3] =
    { vec4(1,0,0,1),
      vec4(1,1,0,1),
      vec4(0,1,0,1)
    };
  glUniform4fv(face_loc, 1, lightColor[color_index]);
  glBindVertexArray(vao[1]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void Light::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model =  RotateY(-90) * model;
    currentdirection = static_cast<direction>((currentdirection + 3) % 4);
    }

void Light::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model =  RotateY(90) * model;
    currentdirection = static_cast<direction>((currentdirection + 1) % 4);
    }

void Light::moveForward() {
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

void Light::moveBackward() {
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
