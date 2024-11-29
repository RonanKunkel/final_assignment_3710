#include "light.h"

// traffic light constructor: 
// takes in: vertex location(vertexloc), face location (faceloc), model location (modelloc)
//current direction: setting starting cardinal direction for movement( north, east, south, west)
Light::Light(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : color_index{0}, vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{

  // defining vertices for model:
  const vec4 point[12] = { 
    //bottom part of the traffic light box
      vec4(-0.05, 0.3, -0.05, 1.0), //v0
      vec4(0.05, 0.3, -0.05, 1.0), //v1
      vec4(0.05, 0.3, 0.05, 1.0), //v2
      vec4(-0.05, 0.3, 0.05, 1.0),//v3
    // top part of the traffic light box
      vec4(-0.15, 0.4, -0.05, 1.0), //v4
      vec4(0.15, 0.4, -0.05, 1.0),//v5
      vec4(0.15, 0.4, 0.05, 1.0),  //v6
      vec4(-0.15, 0.4, 0.05, 1.0), //v7
    //bottom part of post
      vec4(-0.05, 0.0, -0.05, 1.0), //v8
      vec4(0.05, 0.0, -0.05, 1.0),//v9
      vec4(0.05, 0.0, 0.05, 1.0),//v10
      vec4(-0.05, 0.0, 0.05, 1.0),//v11
    };
// face definition:
//numbers correspond to vertices ( "0" = v0)
  const GLuint face[10][4] =
    {
      //traffic light box
     {0,1,2,3},  // bot
     {4,5,6,7},  // top
     {0,1,5,4},  // back
     {2,3,7,6},  // front
     {2,6,5,1},  // left
     {0,4,7,3},   // right
//traffic light post
     {8,9,0,1}, // back
     {11,10,2,3}, //front
     {8,11,3,0}, //left
     {9,10,2,1} //right
    };
  

// generating vertex array objects and buffers.
  glGenVertexArrays(2, vao);
  glGenBuffers(2, buffer);
//binding first vao and buffer to draw the traffic light box.
//passing data into buffer
//drawing first object
  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			  BUFFER_OFFSET(0));

//generating element buffer object
//passing buffer data
  glGenBuffers(10, ebo);
  for (int i = 0; i < 10; i++) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), face[i], GL_STATIC_DRAW);
  }
//binding second vao and second buffer for colour changing light object.
  glBindVertexArray(vao[1]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);

  //defining vertices of colour changing object.
  //object created as a 3d box, clipping through the traffic light and sticking out on both sides.
  vec4 A[8] =
    {
    // front face
     vec4(-0.052, 0.38, 0.052, 1),  vec4(0.052, 0.38, 0.052, 1),
     vec4(0.052, 0.32, 0.052, 1),
     vec4(-0.052, 0.32, 0.052, 1),
    // rear face
    vec4(-0.052, 0.38, -0.053, 1),  vec4(0.052, 0.38, -0.053, 1),
     vec4(0.052, 0.32, -0.053, 1),
     vec4(-0.052, 0.32, -0.053, 1)
    };


//passing buffer data
  glBufferData(GL_ARRAY_BUFFER, sizeof(A), A, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));
//model calculation.
  model = Translate(pos)
    * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
    * Scale(scale_x, scale_y, scale_z);
}
//traffic light destructor: deletes buffers and vaos
Light::~Light()
{
  glDeleteVertexArrays(2, vao);
  glDeleteBuffers(2, buffer);
  glDeleteBuffers(10, ebo);
}
//function for incrementing through colours.
void Light::next_colour()
{
  color_index = (color_index + 1) % 3;
}
//function to draw the traffic light object.
void Light::draw() const
{
//passing information to shader.
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
//binding first vao to draw traffic light object.
  glBindVertexArray(vao[0]);
//looping through object faces and drawing them with colour (0.4,0.4,0.0,1.0).
  for (int i = 0; i < 10; i++) {
    glUniform4fv(face_loc, 1, vec4(0.4, 0.4, 0.0, 1.0));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  }
// defining colours for traffic light colour changing object.
  vec4 lightColor[3] =
    { vec4(1,0,0,1),
      vec4(1,1,0,1),
      vec4(0,1,0,1)
    };
//passing colour information to shader and binding vao 1 for colour changing object drawing.
  glUniform4fv(face_loc, 1, lightColor[color_index]);
  glBindVertexArray(vao[1]);
//defining faces for the 3d box colour changing object.
  GLuint lightfaces[6][4] = {
    {0, 1, 2, 3},// front 
    {4, 5, 6, 7},// back 
    {0, 4, 7, 3},// left 
    {1, 5, 6, 2},// right 
    {3, 2, 6, 7},// top 
    {0, 1, 5, 4} // bottom 
  };
//drawing the 6 faces of the 3d box colour changing object.
  for (int i = 0; i < 6; i++) {
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, lightfaces[i]);
  }
}


// Functions for car movement:
// each object is rotated and traslated the opposite direction the car is meant to rotate/translate.
// creating an illusion of the car moving.
//mmoveLeft: rotates the traffic light object -90 degrees and updates current direction accordingly.
//moveRight: rotates the traffic light object 90 degrees and updates current direction accordingly.
//moveForward: translates the traffic light object according to the current direction.
//moveBackward: translates the traffic light object according to the current direction.
void Light::moveLeft() {
    model =  RotateY(-90) * model;
    currentdirection = static_cast<direction>((currentdirection + 3) % 4);
    }

void Light::moveRight() {
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
