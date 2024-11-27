
#include "Buildings.h"


building1::building1(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
    const vec4 point[10] = {
      vec4(-0.35, 0, 0.35, 1),   // v0
      vec4(0.35, 0, 0.35, 1),   // v1
      vec4(-0.35, 0, -0.35, 1),   // v2
      vec4(0.35, 0,-0.35, 1),    // v3
      vec4(-0.35, 1, 0.35, 1),   // v4
      vec4(0.35, 1, 0.35, 1),   // v5
      vec4(-0.35, 1, -0.35, 1),   // v6
      vec4(0.35, 1,-0.35, 1),    // v7
      vec4 (0,2,0.35,1),   //v8
      vec4 (0,2,-0.35,1)   //v9
    };
    
    
    const vec4 colors[10] = {
vec4(0.58, 0.29, 0.18, 1.0), //wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.4, 0.4, 0.4, 1.0), //grey
vec4(0.4, 0.4, 0.4, 1.0) //grey
    };

    const int face[10][4] = {
      {0,1,5,4}, // front
      {2,0,4,6}, //left
      {1,3,7,5}, //right
      {3,2,6,7}, // back
      {4,5,7,6}, //top
      {2,3,1,0}, //bottom
      {4,5,8,8}, // front roof
      {7,6,9,9},// rear roof
      {4,8,9,6}, // left roof
      {5,7,9,8} // right roof

    };


    glGenVertexArrays(10, vao);
    glGenBuffers(10, buffer);

    for (int i = 0; i < 10; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
          
          
          
          vec4 A[4];
        // No need for size variable since we always use 4 vertices
        for (int j = 0; j < 4; j++) {
            A[j] = point[face[i][j]];
         }
      // vec4 A[4];
      // int size = 0;
      // for (int j = 0; j < 4; j++) {
      //   if (face[i][j] >= 0) {
	    //     A[size++] = point[face[i][j]];
      //   }
      
     
     
      glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }

    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}




building1::~building1()
{
  glDeleteVertexArrays(10, vao);
  glDeleteBuffers(10, buffer);
}

void building1::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
  
const vec4 colors[10] = {
vec4(0.58, 0.29, 0.18, 1.0), //wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.58, 0.29, 0.18, 1.0),//wood
vec4(0.4, 0.4, 0.4, 1.0), //grey
vec4(0.4, 0.4, 0.4, 1.0) //grey
    };

for(int i = 0; i < 10; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colors[i]);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
  // glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}
void building1::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model = RotateY(-90) * model;
        currentdirection = static_cast<direction>((currentdirection + 3) % 4);

}

void building1::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model = RotateY(90) * model;
        currentdirection = static_cast<direction>((currentdirection + 1) % 4);

}

void building1::moveForward() {
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

void building1::moveBackward() {
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

//=============================

building4::building4(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
    const vec4 point[22] = {
//====================
//    Bottom Cube
//====================
  vec4(-0.5, 0, 0.5, 1), // 0
  vec4(0.5, 0, 0.5, 1), // 1
  vec4(0.5, 0, -0.5, 1), // 2
  vec4(-0.5, 0, -0.5, 1), // 3
  vec4(-0.5, 0.5, 0.5, 1), // 4
  vec4(0.5, 0.5, 0.5, 1), // 5
  vec4(0.5, 0.5, -0.5, 1), // 6
  vec4(-0.5, 0.5, -0.5, 1), // 7
//====================
//    Middle Cube
//====================
  vec4(0.5, 0.5, 0, 1), // 8
  vec4(0, 0.5, 0, 1), // 9
  vec4(0, 0.5, 0.5,1), // 10
  vec4(0.5, 1, 0.5, 1), // 11
  vec4(0.5, 1, 0, 1), // 12
  vec4(0, 1, 0, 1), // 13
  vec4(0, 1, 0.5, 1), // 14
//====================
//    Top Cube
//====================
  vec4(0.5, 1, 0.25, 1), // 15
  vec4(0.25, 1, 0.25, 1), // 16
  vec4(0.25, 1, 0.5, 1), // 17
  vec4(0.5, 1.5, 0.5, 1), // 18
  vec4(0.5, 1.5, 0.25, 1), // 19
  vec4(0.25, 1.5, 0.25, 1), // 20
  vec4(0.25, 1.5, 0.5, 1) // 21
};
    
    
const vec4 colours[16] = {
  // Bottom Cube
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  // Middle Cube
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  // Top Cube
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0) // Wood
};


const int face[16][4] = {
//=============
// Bottom Cube
//=============
  {0,1,2,3},
  {0,1,5,4},
  {1,2,6,5},
  {2,3,7,6},
  {3,0,4,7},
  {4,5,6,7},
//============
// Middle Cube
//============
  {10,5,11,14},
  {5,8,12,11},
  {8,12,13,9},
  {9,13,14,10},
  {11,12,13,14},
//============
// Top Cube
//============
  {11,18,21,17},
  {11,15,19,18},
  {15,16,20,19},
  {16,17,21,20},
  {18,19,20,21}
};

    glGenVertexArrays(16, vao);
    glGenBuffers(16, buffer);

    for (int i = 0; i < 16; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
          
          
          
          vec4 A[4];
        // No need for size variable since we always use 4 vertices
        for (int j = 0; j < 4; j++) {
            A[j] = point[face[i][j]];
         }
      // vec4 A[4];
      // int size = 0;
      // for (int j = 0; j < 4; j++) {
      //   if (face[i][j] >= 0) {
	    //     A[size++] = point[face[i][j]];
      //   }
      
     
     
      glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }

    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}




building4::~building4()
{
  glDeleteVertexArrays(16, vao);
  glDeleteBuffers(16, buffer);
}

void building4::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
  
const vec4 colours[16] = {
  // Bottom Cube
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  // Middle Cube
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  vec4(0.4, 0.4, 0.4, 1.0), // Grey
  // Top Cube
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0), // Wood
  vec4(0.58, 0.29, 0.18, 1.0) // Wood
};


for(int i = 0; i < 16; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colours[i]);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
  // glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}
void building4::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model =  RotateY(-90) * model;
    currentdirection = static_cast<direction>((currentdirection + 3) % 4);
    }

void building4::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model =  RotateY(90) * model;
    currentdirection = static_cast<direction>((currentdirection + 1) % 4);
    }

void building4::moveForward() {
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

void building4::moveBackward() {
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