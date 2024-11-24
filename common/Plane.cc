#include "Plane.h"

Plane::Plane(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}
{
    const vec4 point[4] = {
      vec4(7.25, 0, 7.25, 1), 
      vec4(7.25, 0, -7.25, 1),
      vec4(-7.25, 0, -7.25, 1),
      vec4(-7.25, 0, 7.25, 1)
    };

    const int face[1][4] = {
      {0,1,2,3}
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

Plane::~Plane()
{
  glDeleteVertexArrays(1, vao);
  glDeleteBuffers(1, buffer);
}

void Plane::draw() const
{
  glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

  glBindVertexArray(vao[1]);
  glUniform4fv(face_loc, 1, vec4(0,1,0,1));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[0]);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);


  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Plane::moveLeft() {
    // model = model * Translate(-0.5, 0, 0);
    model = model * RotateY(90);
}

void Plane::moveRight() {
    // model = model * Translate(0.5, 0, 0);
    model = model * RotateY(-90);
}

void Plane::moveForward() {
    model = model * Translate(0, 0, -0.5);
}

void Plane::moveBackward() {
    model = model * Translate(0, 0, 0.5);
}