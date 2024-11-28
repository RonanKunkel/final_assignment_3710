#include <Angel.h>
#include <cmath>
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
Plane *plane;
Car *car;
building1 *buildings1[8];
building2 *buildings2[1];
building4 *buildings4[4];
PavementX *pavementsX[9];
PavementZ *pavementsZ[9];

GLfloat camera_theta = M_PI/2, camera_radius = 1.0, modValue = 1.5;

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
  currentCamera->setDefaultView(vec4(0.0, 0.0, 0.0, 1.0));
  currentCamera->sendToShader();

  // Initialize the vertex position attribute from the vertex shader
  GLuint loc = glGetAttribLocation( program, "vPosition" );

  plane = new Plane(loc, faceColourLoc, modelLoc, vec4(0.0, 0.0, 0.0, 1.0));
  car = new Car(loc, faceColourLoc, modelLoc, vec4(0.0, 0.0, 0.0, 1.0));

  vec4 buildingPositions1[8] = {
    vec4(2.25, 0.0001, 2.15, 1.0), vec4(2.25, 0.0001, 3.65, 1.0), vec4(2.25, 0.0001, 5.15, 1.0),
    vec4(2.25, 0.0001, 6.65, 1.0), vec4(5.25, 0.0001, 6.65, 1.0), vec4(5.25, 0.0001, 5.15, 1.0),
    vec4(5.25, 0.0001, 3.65, 1.0), vec4(5.25, 0.0001, 2.15, 1.0)
  };

  vec4 buildingPosition2[1] = {
    vec4(-0.75, 0.0001, -0.75, 1.0)
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

  // building2
  for (int i = 0; i < 1; ++i) {
    buildings2[0] = new building2(loc, faceColourLoc, modelLoc, buildingPosition2[i]);
  }

  vec4 buildingPositions4[4] = {
    vec4(-0.75, 0.0001, 2.15, 1.0), vec4(-0.75, 0.0001, 3.65, 1.0),
    vec4(-0.75, 0.0001, 5.15, 1.0), vec4(-0.75, 0.0001, 6.65, 1.0)
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


  glClearColor( 0.74902, 0.847059, 0.847059, 1.0 ); // black background
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
}


//----------------------------------------------------------------------------


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  plane->draw();
  car->draw();
  for (int i = 0; i < 8; ++i) buildings1[i]->draw();
  // for (int i = 0; i < 1; ++i) buildings2[i]->draw();
  buildings2[0]->draw();
  for (int i = 0; i < 4; ++i) buildings4[i]->draw();
  for (int i = 0; i < 9; ++i) pavementsX[i]->draw();
  for (int i = 0; i < 9; ++i) pavementsZ[i]->draw();

  glutSwapBuffers();
}

//----------------------------------------------------------------------------

void cameraAndMovement(int key, int x, int y) {
  vec4 carPosition = car->getPosition();
  // Mod values for staying on the roads
  GLfloat modXVal = std::fmod(plane->currentPosition.x, 1.5);
  GLfloat modZVal = std::fmod(plane->currentPosition.z, 1.5);

  switch (key) {
    case GLUT_KEY_F1:
      currentCamera->setDefaultView(carPosition);
      break;
    case GLUT_KEY_F2:
      currentCamera->setOverheadView(carPosition);
      break;
    case GLUT_KEY_F3:
      currentCamera->setSideView(carPosition);
      break;
  }

    switch (key) {
    case GLUT_KEY_LEFT:
      if (plane->currentPosition.x == 0.0 && plane->currentPosition.z == 0.0 || modXVal == 0 && modZVal == 0) {
        plane->moveLeft();
        for (int i = 0; i < 8; ++i) buildings1[i]->moveLeft();
        for (int i = 0; i < 1; ++i) buildings2[i]->moveLeft();
        for (int i = 0; i < 4; ++i) buildings4[i]->moveLeft();
        for (int i = 0; i < 9; ++i) pavementsX[i]->moveLeft();
        for (int i = 0; i < 9; ++i) pavementsZ[i]->moveLeft();
        break;
      } else {
        break;
      }

    case GLUT_KEY_RIGHT:
      if (plane->currentPosition.x == 0.0 && plane->currentPosition.z == 0.0 || modXVal == 0 && modZVal == 0) {
        plane->moveRight();
        for (int i = 0; i < 8; ++i) buildings1[i]->moveRight();
        for (int i = 0; i < 1; ++i) buildings2[i]->moveRight();
        for (int i = 0; i < 4; ++i) buildings4[i]->moveRight();
        for (int i = 0; i < 9; ++i) pavementsX[i]->moveRight();
        for (int i = 0; i < 9; ++i) pavementsZ[i]->moveRight();
        break;
      } else {
        break;
      }
    case GLUT_KEY_UP:
      if (plane->getDirection() == 0 && plane->currentPosition.z >= 7) {
      } else if (plane->getDirection() == 2 && plane->currentPosition.z <= -7) {
      } else if (plane->getDirection() == 1 && plane->currentPosition.x >= 7){
      } else if (plane->getDirection() == 3 && plane->currentPosition.x <= -7){
      } else {
      plane->moveForward();
      for (int i = 0; i < 8; ++i) buildings1[i]->moveForward();
      for (int i = 0; i < 1; ++i) buildings2[i]->moveForward();
      for (int i = 0; i < 4; ++i) buildings4[i]->moveForward();
      for (int i = 0; i < 9; ++i) pavementsX[i]->moveForward();
      for (int i = 0; i < 9; ++i) pavementsZ[i]->moveForward();

      break;
      }
    case GLUT_KEY_DOWN:
      if (plane->getDirection() == 0 && plane->currentPosition.z <= -7) {
      } else if (plane->getDirection() == 2 && plane->currentPosition.z >= 7) {
      } else if (plane->getDirection() == 1 && plane->currentPosition.x <= -7){
      } else if (plane->getDirection() == 3 && plane->currentPosition.x >= 7){
      } else {
      plane->moveBackward();
      for (int i = 0; i < 8; ++i) buildings1[i]->moveBackward();
      for (int i = 0; i < 1; ++i) buildings2[i]->moveBackward();
      for (int i = 0; i < 4; ++i) buildings4[i]->moveBackward();
      for (int i = 0; i < 9; ++i) pavementsX[i]->moveBackward();
       for (int i = 0; i < 9; ++i) pavementsZ[i]->moveBackward();
      break;
      }
  }
  
  currentCamera->sendToShader();
  // Used for debugging
  std::cout << "Direction:" << plane->currentPosition << std::endl;
  std::cout << "Direction:" << plane->getDirection() << std::endl;

  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 033: // Escape key
      exit(EXIT_SUCCESS);
      break;
  }
}

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
  
  glutMainLoop();
  return 0;
}