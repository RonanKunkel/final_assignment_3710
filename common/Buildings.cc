
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
      vec4(0.309804, 0.309804, 0.184314, 1.0), //dark olive
      vec4(0.309804, 0.309804, 0.184314, 1.0) //dark olive
    };

for(int i = 0; i < 10; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colors[i]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}
void building1::moveLeft() {
    model = RotateY(-90) * model;
        currentdirection = static_cast<direction>((currentdirection + 3) % 4);
}

void building1::moveRight() {
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
building2::building2(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
    const vec4 point[13] = {
      vec4(-0.40, 0, 0.40, 1),   // v0
      vec4(0.40, 0, 0.40, 1),   // v1
      vec4(-0.40, 0, -0.40, 1),   // v2
      vec4(0.40, 0,-0.40, 1),    // v3
      vec4(-0.40, 3, 0.40, 1),   // v4
      vec4(0.40, 3, 0.40, 1),   // v5
      vec4(-0.40, 3, -0.40, 1),   // v6
      vec4(0.40, 3,-0.40, 1),   // v7
      // door verticies
      vec4(-0.10, 0, 0.41, 1),  // v8
      vec4(0.10, 0, 0.41, 1), // v9
      vec4(0.10, 0.30, 0.41, 1),  // v10
      vec4(-0.10, 0.30, 0.41, 1),  // v11
      // top cone
      vec4(0.0, 3.2, 0.0, 1) // v12
    };

    const int face[11][4] = {
      {0,1,5,4}, // front
      {2,0,4,6}, //left
      {1,3,7,5}, //right
      {3,2,6,7}, // back
      {4,5,7,6}, //top
      {2,3,1,0}, //bottom
      {8,9,10,11}, //door
      {4,5,12},  // top cone 1
      {5,7,12},  // top cone 2
      {7,6,12},  // top cone 3
      {6,4,12}  // top cone 4
    };

    glGenVertexArrays(11, vao);
    glGenBuffers(11, buffer);

    for (int i = 0; i < 11; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
          
          vec4 A[4];
        // No need for size variable since we always use 4 vertices
        for (int j = 0; j < 4; j++) {
            A[j] = point[face[i][j]];
         }
     
      glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec4), A, GL_STATIC_DRAW);
      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }

    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}

building2::~building2()
{
  glDeleteVertexArrays(11, vao);
  glDeleteBuffers(11, buffer);
}

void building2::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
  const vec4 colors[11] = {
    vec4( 0.737255, 0.560784, 0.560784, 1.0), // pink
    vec4( 0.737255, 0.560784, 0.560784, 1.0), // pink
    vec4( 0.737255, 0.560784, 0.560784, 1.0), // pink
    vec4( 0.737255, 0.560784, 0.560784, 1.0), // pink
    vec4( 0.5, 0.5, 0.5, 1.0), 
    vec4( 0.5, 0.5, 0.5, 1.0), 
    vec4( 0.5, 0.5, 0.5, 1.0), 
    vec4( 0.5, 0.5, 0.5, 1.0), 
    vec4( 0.8, 0.8, 0.8, 1.0), 
    vec4( 0.5, 0.5, 0.5, 1.0),
    vec4( 0.8, 0.8, 0.8, 1.0)
  };

  for(int i = 0; i < 11; i++) {
    glBindVertexArray(vao[i]);
    glUniform4fv(face_loc, 1, colors[i]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }
}

void building2::moveLeft() {
    model = RotateY(-90) * model;
        currentdirection = static_cast<direction>((currentdirection + 3) % 4);
}

void building2::moveRight() {
    model = RotateY(90) * model;
        currentdirection = static_cast<direction>((currentdirection + 1) % 4);
}

void building2::moveForward() {
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

void building2::moveBackward() {
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
  //====================================================
building3::building3(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
    const vec4 point[18] = {
      //building 1 
      //face 1 
      vec4(0.05/3, 0, 0.5/3, 1), //v0
      vec4(0.05/3, 0, 0, 1), //v1 
      vec4(0.05/3, 3.0/3, 0, 1), //v2
      vec4(0.05/3, 3.0/3, 0.5/3, 1), //v3 
      //face 2 
      vec4(-0.05/3,0,0.5/3,1), //v4
      vec4(-0.05/3,3.0/3,0.5/3,1), //v5  
      vec4(-0.05/3,3.0/3,0,1), //v6 
      vec4(-0.05/3,0,0,1), //7 
      //building2 
      //face 1 
      //using points from bulding 1 face 1 plus 
      vec4(0.5/3,0,-0.4/3, 1), //v8
      vec4(0.5/3,3.0/3,-0.4/3, 1), //v9
      //face2 
      vec4(0.4/3,0,-0.5/3, 1), //v10
      vec4(0.4/3,3.0/3,-0.5/3, 1), //v11
      //face 3 
      vec4(0,0,0.1/3,1), //v12
      vec4(0,3.0/3,0.1/3,1), //v13
      //building 4 
      //face 1 
      vec4(-0.4/3,0,-0.5/3,1), //v14
      vec4(-0.4/3,3.0/3,-0.5/3,1), //15
      //face2
      vec4(-0.5/3,0,-0.4/3,1), //16
      vec4(-0.5/3,3.0/3,-0.4/3,1) //17        
    };
    
    
    const vec4 colors[13] = {
      vec4(0.8,0.49,0.19,1), //gold 
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1),
      vec4(0.8,0.49,0.19,1)
    };

    const int face[13][4] = {
      //wing 1 
      {1,2,3,0}, //face 1
      {4,0,3,5}, //face 2 
      {4,5,6,7}, //face 3 
      {3,2,6,5}, //roof
      //wing 2 
      {1,8,9,2}, //face 1 
      {8,10,11,9}, //face 2 
      {11,10,12,13}, //face 3 
      {9,11,13,2}, //roof
      //wing 3
      {13,12,14,15}, //face 1 
      {15,14,16,17}, //face 2 
      {17,16,7,6}, //face 3
      {15,17,6,13},//roof 
      //center 
      {6,2,13,13} //roof  
      

    };


    glGenVertexArrays(13, vao);
    glGenBuffers(13, buffer);

    for (int i = 0; i < 13; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
          
          
          
          vec4 A[4];
        // No need for size variable since we always use 4 vertices
        for (int j = 0; j < 4; j++) {
            A[j] = point[face[i][j]];
         }
     
      glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }

    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}




building3::~building3()
{
  glDeleteVertexArrays(13, vao);
  glDeleteBuffers(13, buffer);
}

void building3::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
  
const vec4 colors[13] = {
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1),
vec4(0.8,0.49,0.19,1)
    };

for(int i = 0; i < 13; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colors[i]);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
  // glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}
void building3::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model = RotateY(-90) * model;
        currentdirection = static_cast<direction>((currentdirection + 3) % 4);

}


void building3::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model = RotateY(90) * model;
        currentdirection = static_cast<direction>((currentdirection + 1) % 4);

}

void building3::moveForward() {
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

void building3::moveBackward() {
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
  building5::building5(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}, currentdirection{direction::north}
{
    const vec4 point[10] = {
//bottom of pyrymid 
vec4(-0.4/2,0,0.4/2,1), //v0
vec4(0.4/2,0,0.4/2,1), //v1
vec4(0.4/2,0,-0.4/2,1),  //v2
vec4(-0.4/2,0,-0.4/2,1), //v3
//center
vec4(0,1.0/2,0,1),  //v4

//top pyramid
vec4(0.4/2,1.5/2,0.4/2,1),  //v5
vec4(0.4/2,1.5/2,0.4/2,1), //v6
vec4(-0.4/2,1.5/2,-0.4/2,1), //v7
vec4(-0.4/2,1.5/2,0.4/2,1), //v8
vec4(0,0.75/2,0,1),  //v9

};
    
    
const vec4 colours[10] = {
  // Bottom Cube
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0) // medium Aquamarine

};


const int face[10][4] = {
//=============
// Bottom pyrimid
//=============
// {1,2,3,4},
// {1,2,5,5},
// {2,3,5,5},
// {3,4,5,5},
// {5,1,4,4},

{0,1,2,3}, // bottom
{0,1,4,4}, //  side1
{1,2,4,4}, // side2
{2,3,4,4}, // side 3
{4,0,3,3}, // side 4
//second pyrmid 
{8,5,6,7}, //
{5,9,6,6}, //
{6,9,7,7}, // 
{7,9,8,8}, //
{8,9,5,5} //
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




building5::~building5()
{
  glDeleteVertexArrays(10, vao);
  glDeleteBuffers(10, buffer);
}

void building5::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);
  
const vec4 colours[10] = {
  // Bottom Cube
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0), // medium Aquamarine
  vec4(0.196, 0.8, 0.6, 1.0) // medium Aquamarine
};


for(int i = 0; i < 10; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colours[i]);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
  // glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}
void building5::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model =  RotateY(-90) * model;
    currentdirection = static_cast<direction>((currentdirection + 3) % 4);
    }

void building5::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model =  RotateY(90) * model;
    currentdirection = static_cast<direction>((currentdirection + 1) % 4);
    }

void building5::moveForward() {
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

void building5::moveBackward() {
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