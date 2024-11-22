#include <Angel.h>
#include "Object.h"
#include "Wheels.h"
#include "Traffic_Light.h"
#include "Plane.h"
#include "Car.h"
#include "Camera.h"
#include "Buildings.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
Plane  *plane; 
Camera *camera;

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
  plane = new Plane(loc, faceColourLoc, modelLoc, vec4(0,0,0,0));

  vec4 eye(0, 15, 5, 1);    // Both up and slightly back
  vec4 at(0, 0, 0, 1);      // Looking at center
  vec4 up(0, 1, 0, 0);      // Y axis as up direction
  camera = new Camera(viewLoc, projLoc, eye, at, up, -10, 10, -10, 10, -1, 100);
  
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

  camera->sendToShader();
  plane->draw();

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
    use_perspective = !use_perspective;
    glutPostRedisplay();
    break;
  }
}

void arrow(int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_LEFT:
    camera->moveEye(-0.2, 0, 0);
    break;
  case GLUT_KEY_RIGHT:
    camera->moveEye(0.2, 0, 0);
    break;
  case GLUT_KEY_UP:
    camera->moveEye(0, -0.2, -0.2);
    break;
  case GLUT_KEY_DOWN:
    camera->moveEye(0, 0.2, 0.2);
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
  glutInitWindowSize(1024, 1024);

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