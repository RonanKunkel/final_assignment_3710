#include "Car.h"


Car::Car(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc,
        vec4 pos, GLfloat theta_x, GLfloat theta_y,GLfloat theta_z,
        GLfloat scale_x,GLfloat scale_y,GLfloat scale_z)
        : vertex_loc{vertexLoc}, face_loc{faceLoc},
        model_loc{modelLoc}
    {
        const vec4 point[8] = {
            vec4(-0.125, 0.0002, -0.1625, 1), //0
            vec4(-0.125, 0.25, -0.1625 ,1), //1
            vec4(0.125, 0.25, -0.1625 ,1), //2
            vec4(0.125, 0.0002, -0.1625, 1), //3
            vec4(-0.125, 0.0002, 0.1625, 1), //4 
            vec4(0.125, 0.0002, 0.1625, 1),//5
            vec4(0.125, 0.25, 0.1625 ,1), //6
            vec4(-0.125, 0.25, 0.1625, 1) //7
        };

        const vec4 colors[5] = {
vec4(0.8, 0.498039, 0.196078, 1.0), // Front Face Gold
vec4(0.137255, 0.419608, 0.556863, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0) // Steel Blue
        };

        const int face [5][4] = {
            {0,1,2,3},
            {4,7,1,0},
            {4,5,6,7},
            {5,6,2,3},
            {7,6,2,1}
        };


        glGenVertexArrays(5, vao);
        glGenBuffers(5, buffer);

    for (int i = 0; i < 5; i++) {
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

    model = Translate(pos) * RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z)
            * Scale(scale_x, scale_y, scale_z);

    }

Car::~Car() 
{
    glDeleteVertexArrays(5, vao);
    glDeleteBuffers(5, buffer);
}


void Car::draw() const {
        glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

        const vec4 colors[5] = {
vec4(0.8, 0.498039, 0.196078, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0), // Steel Blue
vec4(0.137255, 0.419608, 0.556863, 1.0) // Steel Blue
        };

for(int i = 0; i < 5; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colors[i]);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
  // glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}

vec4 Car::getPosition() const {
    return vec4(model[3][0], model[3][1], model[3][2], 1.0);
}
