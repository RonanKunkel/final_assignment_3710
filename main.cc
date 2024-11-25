#include <Angel.h>
#include "Object.h"
#include "Wheels.h"
#include "Traffic_Light.h"
#include "Plane.h"
#include "Car.h"
#include "Camera.h"
#include "CameraGTA.h"
#include "Buildings.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
Plane  *plane; 
building1 *building;
building1 *buildinga;
building1 *buildingb;
building1 *buildingc;
building1 *buildingd;
building1 *buildinge;
building1 *buildingf;
building1 *buildingg;
building4 *buildingr;
building4 *buildingro;
building4 *buildingron;
building4 *buildingrona;

CameraGTA *cameraP;
Camera *cameraO;
int cameraChoice = 0;
vec4 pos(0.0, 0.0, 0.0, 1.0);

bool use_perspective = false;
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

  // Initialize the vertex position attribute from the vertex shader
  GLuint loc = glGetAttribLocation( program, "vPosition" );

  // Create the plane
  plane = new Plane(loc, faceColourLoc, modelLoc, pos);
  building = new building1(loc, faceColourLoc, modelLoc, vec4(2.0,0.1,2.0,1.0));
  buildinga = new building1(loc, faceColourLoc, modelLoc, vec4(2.0,0.1,3.5,1.0));
  buildingb = new building1(loc, faceColourLoc, modelLoc, vec4(2.0,0.1,5.0,1.0));
  buildingc = new building1(loc, faceColourLoc, modelLoc, vec4(2.0,0.1,6.5,1.0));
  buildingd = new building1(loc, faceColourLoc, modelLoc, vec4(5.0,0.1,6.5,1.0));
  buildinge = new building1(loc, faceColourLoc, modelLoc, vec4(5.0,0.1,5.0,1.0));
  buildingf = new building1(loc, faceColourLoc, modelLoc, vec4(5.0,0.1,3.5,1.0));
  buildingg = new building1(loc, faceColourLoc, modelLoc, vec4(5.0,0.1,2.0,1.0));
  buildingr = new building4(loc, faceColourLoc, modelLoc, vec4(-1.0,0.1,2.0,1.0 ));
  buildingro = new building4(loc, faceColourLoc, modelLoc, vec4(-1.0,0.1,3.5,1.0 ));
  buildingron = new building4(loc, faceColourLoc, modelLoc, vec4(-1.0,0.1,5.0,1.0 ));
  buildingrona = new building4(loc, faceColourLoc, modelLoc, vec4(-1.0,0.1,6.5,1.0 ));




  // gta style
  cameraP = CameraGTA::createGTACamera(viewLoc, projLoc);
  // top down (Orhto)
  cameraO = Camera::createOrthoCamera(viewLoc, projLoc);
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

  if (cameraChoice == 1) {
    cameraO->sendToShader();
  } else {
    cameraP->sendToShader();
  }

  plane->draw();
  building->draw();
  buildinga->draw();
  buildingb->draw();
  buildingc->draw();
  buildingd->draw();
  buildinge->draw();
  buildingf->draw();
  buildingg->draw();
  buildingr->draw();
  buildingro->draw();
  buildingron->draw();
  buildingrona->draw();


  glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
  switch ( key ) {
  case 033:
    exit( EXIT_SUCCESS );
    break;
  case 'p':
    // use_perspective = !use_perspective;
    glutPostRedisplay();
    break;
  case 'a':
    cameraChoice = 1;
    glutPostRedisplay();
    break;
  case 's':
    cameraChoice = 0;
    glutPostRedisplay();
  }
}

void arrow(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_LEFT:
    plane->moveLeft();
    building->moveLeft();
buildinga->moveLeft();
buildingb->moveLeft();
buildingc->moveLeft();
buildingd->moveLeft();
buildinge->moveLeft();
buildingf->moveLeft();
buildingg->moveLeft();
buildingr->moveLeft();
buildingro->moveLeft();
buildingron->moveLeft();
buildingrona->moveLeft();

    break;
  case GLUT_KEY_RIGHT:
    plane->moveRight();
    building->moveRight();
buildinga->moveRight();
buildingb->moveRight();
buildingc->moveRight();
buildingd->moveRight();
buildinge->moveRight();
buildingf->moveRight();
buildingg->moveRight();
buildingr->moveRight();
buildingro->moveRight();
buildingron->moveRight();
buildingrona->moveRight();

    break;
  case GLUT_KEY_UP:
    plane->moveForward();
    building->moveForward();
buildinga->moveForward();
buildingb->moveForward();
buildingc->moveForward();
buildingd->moveForward();
buildinge->moveForward();
buildingf->moveForward();
buildingg->moveForward();
buildingr->moveForward();
buildingro->moveForward();
buildingron->moveForward();
buildingrona->moveForward();

    break;
  case GLUT_KEY_DOWN:
    plane->moveBackward();
   building->moveBackward();
buildinga->moveBackward();
buildingb->moveBackward();
buildingc->moveBackward();
buildingd->moveBackward();
buildinge->moveBackward();
buildingf->moveBackward();
buildingg->moveBackward();
buildingr->moveBackward();
buildingro->moveBackward();
buildingron->moveBackward();
buildingrona->moveBackward();

    break;
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
  }
  glutPostRedisplay();
}

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

// note: on some platform the following doesn't work
void mouse_wheel(int wheel, int dir, int x, int y)
{
  if (dir > 0) {
    camera_radius -= 0.1;
    if (camera_radius < 1.0)
      camera_radius = 1.0;
  } else {
    camera_radius += 0.1;
  }
  glutPostRedisplay();
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

  glutCreateWindow("Triangular Prism");

  glewInit();

  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrow);
  glutMouseFunc(mouse_button);
  glutMouseWheelFunc(mouse_wheel);
  
  glutMainLoop();
  return 0;
}