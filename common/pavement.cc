#include "Pavement.h"

PavementX::PavementX(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}
{
    const vec4 point[4] = {
      vec4(-0.25, 0.0001, 7.25, 1), //v0
      vec4(0.25, 0.0001, 7.25, 1),  //v1
      vec4(-0.25, 0.0001, -7.25, 1), //v2
      vec4(0.25, 0.0001, -7.25, 1) //v3
    };

    const int face[1][4] = {
      {0,1,3,2}
    };
    glGenVertexArrays(1, vao);
    glGenBuffers(1, buffer);

    for (int i = 0; i < 1; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);

      vec4 A[4];
      int size = 0;
      for (int j = 0; j < 4; j++) {
        if (face[i][j] >= 0) {
	        A[size++] = point[face[i][j]];
        }
      }
      glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }

    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}

PavementX::~PavementX()
{
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, buffer);
}

void PavementX::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

  glBindVertexArray(vao[1]);
  glUniform4fv(face_loc, 1, vec4(0.4,0.4,0.4,1));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[0]);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);


  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void PavementX::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model = RotateY(90) * model;
}

void PavementX::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model = RotateY(-90) * model;
}

void PavementX::moveForward() {
    model = model * Translate(0, 0, -0.5);
}

void PavementX::moveBackward() {
    model = model * Translate(0, 0, 0.5);
}



PavementZ::PavementZ(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}
{
    const vec4 point[4] = {

      vec4(7.25, 0.0001, -0.25, 1), //v0
      vec4(7.25, 0.0001, 0.25, 1),  //v1
      vec4(-7.25, 0.0001, -0.25, 1), //v2
      vec4(-7.25, 0.0001, 0.25, 1) //v3

    };

    const int face[1][4] = {
      {0,1,3,2}
    };
    glGenVertexArrays(1, vao);
    glGenBuffers(1, buffer);

    for (int i = 0; i < 1; i++) {
      glBindVertexArray(vao[i]);

      // initialize a buffer object
      glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);

      vec4 A[4];
      int size = 0;
      for (int j = 0; j < 4; j++) {
        if (face[i][j] >= 0) {
	        A[size++] = point[face[i][j]];
        }
      }
      glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec4), A, GL_STATIC_DRAW);

      glEnableVertexAttribArray( vertexLoc );
      glVertexAttribPointer( vertexLoc, 4, GL_FLOAT, GL_FALSE, 0,
	  		   BUFFER_OFFSET(0) );
    }

    model = Translate(pos)
      * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
      * Scale(scale_x, scale_y, scale_z);
}

PavementZ::~PavementZ()
{
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, buffer);
}

void PavementZ::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

  glBindVertexArray(vao[1]);
  glUniform4fv(face_loc, 1, vec4(0.4,0.4,0.4,1));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[0]);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);


  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void PavementZ::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model = RotateY(90) * model;
}

void PavementZ::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model = RotateY(-90) * model;
}

void PavementZ::moveForward() {
    model = model * Translate(0, 0, -0.5);
}

void PavementZ::moveBackward() {
    model = model * Translate(0, 0, 0.5);
}