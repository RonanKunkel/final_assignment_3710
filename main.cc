#include <Angel.h>
#include "Object.h"
#include "Wheels.h"
#include "Traffic_Light.h"
#include "Plane.h"
#include "Car.h"
#include "Camera.h"
#include "Buildings.h"
#include "Pavement.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
Camera *currentCamera;
vec4 car_position(0.0, 0.0, 0.0, 1.0);


Plane  *plane; 
building1 *buildings1[8];
building4 *buildings4[4];
PavementX *pavementsX[9];
PavementZ *pavementsZ[9];

GLfloat camera_theta = M_PI/2, camera_radius = 1.0;

void init()
{

  GLint faceColourLoc, modelLoc, viewLoc, projLoc;

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("shaders/vshader.glsl", "shaders/fshader.glsl");
  glUseProgram(program);

  faceColourLoc = glGetUniformLocation(program, "uFaceColour");
  modelLoc = glGetUniformLocation(program, "uModel");
  viewLoc = glGetUniformLocation(program, "uView");
  projLoc = glGetUniformLocation(program, "uProjection");

  currentCamera = Camera::createPerspectiveCamera(viewLoc, projLoc);
  currentCamera->setDefaultView(car_position);
  currentCamera->sendToShader();

  // Initialize the vertex position attribute from the vertex shader
  GLuint loc = glGetAttribLocation( program, "vPosition" );

  plane = new Plane(loc, faceColourLoc, modelLoc, vec4(0.0, 0.0, 0.0, 1.0));

  vec4 buildingPositions1[8] = {
    vec4(2.25, 0.1, 2.15, 1.0), vec4(2.25, 0.1, 3.65, 1.0), vec4(2.25, 0.1, 5.15, 1.0),
    vec4(2.25, 0.1, 6.65, 1.0), vec4(5.25, 0.1, 6.65, 1.0), vec4(5.25, 0.1, 5.15, 1.0),
    vec4(5.25, 0.1, 3.65, 1.0), vec4(5.25, 0.1, 2.15, 1.0)

  };

vec4 PavementpositonX[9]={
   vec4(-6.0, 0.0001, 0.0, 1.0), vec4(-4.5, 0.0001, 0.0, 1.0), vec4(-3.0, 0.0001, 0.0, 1.0),
    vec4(-1.5, 0.0001, 0.0, 1.0), vec4(0.0, 0.0001, 0.0, 1.0), vec4(1.5, 0.0001, 0.0, 1.0),
    vec4(3.0, 0.0001, 0.0, 1.0), vec4(4.5, 0.0001, 0.0, 1.0), vec4(6.0,0.0001,0.0,1.0)

};
vec4 PavementpositonZ[9]={
   vec4(0.0, 0.0001, -6.0, 1.0), vec4(0.0, 0.0001, -4.5, 1.0), vec4(0.0, 0.0001, -3.0, 1.0),
    vec4(0.0, 0.0001, -1.5, 1.0), vec4(0.0, 0.0001, 0.0, 1.0), vec4(0.0, 0.0001, 1.5, 1.0),
    vec4(0.0, 0.0001, 3.0, 1.0), vec4(0.0, 0.0001, 4.5, 1.0), vec4(0.0,0.0001,6.0,1.0)

};

  for (int i = 0; i < 8; ++i) {
    buildings1[i] = new building1(loc, faceColourLoc, modelLoc, buildingPositions1[i]);
  }

  vec4 buildingPositions4[4] = {
    vec4(-0.75, 0.1, 2.15, 1.0), vec4(-0.75, 0.1, 3.65, 1.0),
    vec4(-0.75, 0.1, 5.15, 1.0), vec4(-0.75, 0.1, 6.65, 1.0)
  };

  for (int i = 0; i < 4; ++i) {
    buildings4[i] = new building4(loc, faceColourLoc, modelLoc, buildingPositions4[i]);
  }

  for (int i = 0; i < 9; ++i) {
    pavementsX[i] = new PavementX(loc, faceColourLoc, modelLoc, PavementpositonX[i]);
  }
  
  for (int i = 0; i < 9; ++i) {
    pavementsZ[i] = new PavementZ(loc, faceColourLoc, modelLoc, PavementpositonZ[i]);
  }


  glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
}


//----------------------------------------------------------------------------

// mat4 get_projection(mat4 modelview)
// {
//   GLfloat z1 = 1e10, z2 = -1e10;
  
//   for (int i = 0; i < 4; i++) {
//     auto p = modelview * point[i];
//     z1 = min(z1, -p.z);
//     z2 = max(z2, -p.z);
//   }

//   GLfloat nearPlane, farPlane;

//   if (use_perspective) {
//     nearPlane = z1 - 0.01;
//     farPlane = z2 + 0.01;
//     return Perspective(120, 1.0, nearPlane, farPlane);
//   } else {
//     nearPlane = z1 - 0.5;
//     farPlane = z2 + 0.5;
//     return Ortho(-8.0, 8.0, -8.0, 8.0, nearPlane, farPlane);
//   }
// }

void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  plane->draw();
  for (int i = 0; i < 8; ++i) buildings1[i]->draw();
  for (int i = 0; i < 4; ++i) buildings4[i]->draw();
  for (int i = 0; i < 9; ++i) pavementsX[i]->draw();
  for (int i = 0; i < 9; ++i) pavementsZ[i]->draw();

  glutSwapBuffers();
}

//----------------------------------------------------------------------------

void cameraAndMovement(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_F1:
      currentCamera->setDefaultView(car_position);
      break;
    case GLUT_KEY_F2:
      currentCamera->setOverheadView(car_position);
      break;
    case GLUT_KEY_F3:
      currentCamera->setSideView(car_position);
      break;
  }

    switch (key) {
    case GLUT_KEY_LEFT:
      plane->moveLeft();
      for (int i = 0; i < 8; ++i) buildings1[i]->moveLeft();
      for (int i = 0; i < 4; ++i) buildings4[i]->moveLeft();
      for (int i = 0; i < 9; ++i) pavementsX[i]->moveLeft();
      for (int i = 0; i < 9; ++i) pavementsZ[i]->moveLeft();

      break;
    case GLUT_KEY_RIGHT:
      plane->moveRight();
      for (int i = 0; i < 8; ++i) buildings1[i]->moveRight();
      for (int i = 0; i < 4; ++i) buildings4[i]->moveRight();
      for (int i = 0; i < 9; ++i) pavementsX[i]->moveRight();
      for (int i = 0; i < 9; ++i) pavementsZ[i]->moveRight();

      break;
    case GLUT_KEY_UP:
      plane->moveForward();
      for (int i = 0; i < 8; ++i) buildings1[i]->moveForward();
      for (int i = 0; i < 4; ++i) buildings4[i]->moveForward();
      for (int i = 0; i < 9; ++i) pavementsX[i]->moveForward();
      for (int i = 0; i < 9; ++i) pavementsZ[i]->moveForward();

      break;
    case GLUT_KEY_DOWN:
      plane->moveBackward();
      for (int i = 0; i < 8; ++i) buildings1[i]->moveBackward();
      for (int i = 0; i < 4; ++i) buildings4[i]->moveBackward();
      for (int i = 0; i < 9; ++i) pavementsX[i]->moveBackward();
       for (int i = 0; i < 9; ++i) pavementsZ[i]->moveBackward();

      break;
  }
  
  currentCamera->sendToShader();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 033: // Escape key
      exit(EXIT_SUCCESS);
      break;
    // case 'p': 
    //   currentCamera->setProjection(Perspective(45.0, 1.0, 0.1, 100.0));
    //   currentCamera->sendToShader();
    //   glutPostRedisplay();
    //   break;
  }
}


// void arrow(int key, int x, int y) {
//   switch (key) {
//     case GLUT_KEY_LEFT:
//       plane->moveLeft();
//       for (int i = 0; i < 8; ++i) buildings1[i]->moveLeft();
//       for (int i = 0; i < 4; ++i) buildings4[i]->moveLeft();
//       for (int i = 0; i < 9; ++i) pavements[i]->moveLeft();
//       break;
//     case GLUT_KEY_RIGHT:
//       plane->moveRight();
//       for (int i = 0; i < 8; ++i) buildings1[i]->moveRight();
//       for (int i = 0; i < 4; ++i) buildings4[i]->moveRight();
//       for (int i = 0; i < 9; ++i) pavements[i]->moveRight();
//       break;
//     case GLUT_KEY_UP:
//       plane->moveForward();
//       for (int i = 0; i < 8; ++i) buildings1[i]->moveForward();
//       for (int i = 0; i < 4; ++i) buildings4[i]->moveForward();
//       for (int i = 0; i < 9; ++i) pavements[i]->moveForward();
//       break;
//     case GLUT_KEY_DOWN:
//       plane->moveBackward();
//       for (int i = 0; i < 8; ++i) buildings1[i]->moveBackward();
//       for (int i = 0; i < 4; ++i) buildings4[i]->moveBackward();
//       for (int i = 0; i < 9; ++i) pavements[i]->moveBackward();
//       break;
//   }

  // case GLUT_KEY_PAGE_UP:
  //   scale *= 1.05;
  //   break;
  // case GLUT_KEY_PAGE_DOWN:
  //   scale *= 1.0/1.05;
  //   break;
  // case GLUT_KEY_HOME:
  //   theta_x += 0.5;
  //   break;
  // case GLUT_KEY_END:
  //   theta_y += 0.5;
  //   break;
  // case GLUT_KEY_INSERT:
  //   theta_z += 0.5;
  //   break;

//   glutPostRedisplay();
// }

void mouse_button(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
      camera_theta -= 0.2;
      break;
    case GLUT_RIGHT_BUTTON:
      camera_theta += 0.2;
      break;
    case 3:
      camera_radius -= 0.1;
      if (camera_radius < 1.0) {
	camera_radius = 1.0;
      }
      break;
    case 4:
      camera_radius += 0.1;
      break;
    }
    glutPostRedisplay();
  }
}

// // note: on some platform the following doesn't work
// void mouse_wheel(int wheel, int dir, int x, int y)
// {
//   if (dir > 0) {
//     camera_radius -= 0.1;
//     if (camera_radius < 1.0)
//       camera_radius = 1.0;
//   } else {
//     camera_radius += 0.1;
//   }
//   glutPostRedisplay();
// }

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512, 512);

  // If you are using freeglut, the next two lines will check if 
  // the code is truly 3.2. Otherwise, comment them out
    
  glutInitContextVersion(3, 2);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutCreateWindow("City Simulation");

  glewInit();

  init();

  glutDisplayFunc(display);
  glutSpecialFunc(cameraAndMovement);
  glutKeyboardFunc(keyboard);
  // glutSpecialFunc(arrow);
  glutMouseFunc(mouse_button);
  // glutMouseWheelFunc(mouse_wheel);
  
  glutMainLoop();
  return 0;
}