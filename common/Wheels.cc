#include "Wheels.h"


Wheels::Wheels(GLuint vertexLoc, GLuint faceLoc, GLuint modelLoc,
        vec4 pos, GLfloat theta_x, GLfloat theta_y,GLfloat theta_z,
        GLfloat scale_x,GLfloat scale_y,GLfloat scale_z)
        : vertex_loc{vertexLoc}, face_loc{faceLoc},
        model_loc{modelLoc}
    {
       
        const vec4 point[36] = {
            vec4(0,0,0,1), //0
            vec4(0, 0.03*sin(36), 0.03*cos(36), 1), //1
            vec4(0, 0.03*sin(72), 0.03*cos(72), 1), //2
            vec4(0, 0.03*sin(108), 0.03*cos(108), 1), //3
            vec4(0, 0.03*sin(144), 0.03*cos(144), 1), //4
            vec4(0, 0.03*sin(180), 0.03*cos(180), 1), //5
            vec4(0, 0.03*sin(216), 0.03*cos(216), 1), //6
            vec4(0, 0.03*sin(252), 0.03*cos(252), 1), //7
            vec4(0, 0.03*sin(288), 0.03*cos(288), 1), //8
            vec4(0, 0.03*sin(324), 0.03*cos(324), 1), //9
            vec4(0, 0.03*sin(360), 0.03*cos(360), 1), //10
            vec4(0, 0.03*sin(0), 0.03*cos(0), 1), //11
            //back face tire
            vec4(-0.03,0,0,1), //12
            vec4(-0.03, 0.03*sin(36), 0.03*cos(36), 1), //13
            vec4(-0.03, 0.03*sin(72), 0.03*cos(72), 1), //14
            vec4(-0.03, 0.03*sin(108), 0.03*cos(108), 1), //15
            vec4(-0.03, 0.03*sin(144), 0.03*cos(144), 1), //16
            vec4(-0.03, 0.03*sin(180), 0.03*cos(180), 1), //17
            vec4(-0.03, 0.03*sin(216), 0.03*cos(216), 1), //18
            vec4(-0.03, 0.03*sin(252), 0.03*cos(252), 1), //19
            vec4(-0.03, 0.03*sin(288), 0.03*cos(288), 1), //20
            vec4(-0.03, 0.03*sin(324), 0.03*cos(324), 1), //21
            vec4(-0.03, 0.03*sin(360), 0.03*cos(360), 1), //22
            vec4(-0.03, 0.03*sin(0), 0.03*cos(0), 1), //23
            //rim 
            //first 
            vec4(0.0001,0.03*0.8,0.03*-0.2,1),//24
            vec4(0.0001,0.03*0.2,0.03*-0.2,1),//25
            vec4(0.0001,0.03*0.2,0.03*0.2,1), //26
            vec4(0.0001,0.03*0.8,0.03*0.2,1), //27
            //second 
            vec4(0.0001,0.03*0.2,0.03*0.8,1),//28
            vec4(0.0001,0.03*-0.2,0.03*0.8,1), //29
            vec4(0.0001,0.03*-0.2,0.03*0.2,1),//30
            //third
            vec4(0.0001,0.03*-0.8,0.03*0.2,1),//31
            vec4(0.0001,0.03*-0.8,0.03*-0.2,1),//32
            vec4(0.0001,0.03*-0.2,0.03*-0.2,1),//33
            //fourth
            vec4(0.0001,0.03*-0.2,0.03*-0.8,1),//34
            vec4(0.0001,0.03*0.2,0.03*-0.8,1)//35
        };



        const int face [39][4] = {
            //outer tire 
            {0,7,3,3},
            {0,3,10,10},
            {0,10,6,6},
            {0,6,2,2}, 
            {0,2,9,9},
            {0,9,5,5},
            {0,5,1,1},
            {0,1,8,8},
            {0,8,4,4},
            {0,4,11,11},
            {0,11,7,7},
            //inner tire
            {12,19,23,23},
            {12,23,16,16},
            {12,16,20,20},
            {12,20,13,13},
            {12,13,17,17},
            {12,17,21,21},
            {12,21,14,14},
            {12,14,18,18},
            {12,18,22,22},
            {12,22,15,15},
            {12,15,19,19},
            {12,19,23,23},
            //face of tire
            {10,22,15,3},
            {6,18,22,10},
            {2,14,18,6},
            {9,21,14,2},
            {5,17,21,9},
            {1,13,17,5},
            {8,20,13,1},
            {4,16,20,8},
            {11,23,16,4},
            {7,19,23,11},
            {3,15,7,19},
            //rim 
            {24,25,26,27},
            {26,30,29,28},
            {33,32,31,30},
            {35,34,33,25},
            {25,33,30,26}


        };


        glGenVertexArrays(39, vao);
        glGenBuffers(39, buffer);

    for (int i = 0; i < 39; i++) {
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

Wheels::~Wheels() 
{
    glDeleteVertexArrays(34, vao);
    glDeleteBuffers(34, buffer);
}


void Wheels::draw() const {
        glUniformMatrix4fv(model_loc, 1, GL_TRUE, model);

        const vec4 colors[39] = {
            //wheels black 
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            vec4(0, 0, 0, 1),
            //rim
            vec4(0.556, 0.137, 0.419, 1),
            vec4(0.439, 0.576, 0.858,1),
            vec4(0.556, 0.137, 0.419, 1),
            vec4(0.439, 0.576, 0.858,1),
            vec4(0.72, 0.45, 0.20, 1)
        };

for(int i = 0; i < 39; i++) {
  glBindVertexArray(vao[i]);
  glUniform4fv(face_loc, 1, colors[i]);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[i]);
  // glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
}

void Wheels::moveForward(){
    model = model* RotateX(-90);
}
void Wheels::moveBackward(){
    model = model* RotateX(90);
}
