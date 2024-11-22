#include "Plane.h"

Plane::Plane(GLuint vertexLoc, GLuint faceLoc,
	     GLuint modelLoc, vec4 pos,
	     GLfloat theta_x, GLfloat theta_y, GLfloat theta_z,
	     GLfloat scale_x, GLfloat scale_y, GLfloat scale_z)
  : vertex_loc{vertexLoc}, face_loc{faceLoc},
    model_loc{modelLoc}
{
    GLuint vao[1], buffer[1];

    // const vec4 point[4] = {
    //   vec4(7.25, 0, 7.25, 1), 
    //   vec4(7.25, 0, -7.25, 1),
    //   vec4(-7.25, 0, -7.25, 1),
    //   vec4(-7.25, 0, 7.25, 1)
    // };
    const vec4 point[4] = {
      vec4(1, 0, 1, 1), 
      vec4(1, 0, -1, 1),
      vec4(-1, 0, -1, 1),
      vec4(-1, 0, 1, 1)
    };
    const int face[1][4] = {
      {0,1,2,3}
    };
  
  glGenVertexArrays(1, vao);
  glGenBuffers(1, buffer);

  glBindVertexArray(vao[0]);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
  glEnableVertexAttribArray(vertex_loc);
  glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, 0,
			  BUFFER_OFFSET(0));

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

  glBindVertexArray(vao[0]);
    glUniform4fv(face_loc, 1, vec4(0,1,0,1));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[0]);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

  vec4 lightColor[3] =
    { vec4(1,0,0,1),
      vec4(1,1,0,1),
      vec4(0,1,0,1)
    };
  glBindVertexArray(vao[1]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}