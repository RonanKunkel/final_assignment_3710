#include <Angel.h>

#include <iostream>
using namespace std;

//----------------------------------------------------------------------------

GLfloat theta_x = 0.0, theta_y = 0.0, theta_z = 0.0;

vec4 pos(0.0, 0.0, 0.0, 0.0);
vec3 scale(1.0, 1.0, 1.0);
GLint faceColourLoc, modelViewLoc, projLoc;
GLuint vao[2], buffer[2];

bool use_perspective = false;
GLfloat camera_theta = M_PI/2, camera_radius = 1.0;

const vec4 point[4] = {
  vec4(7.25, 0, 7.25, 1), 
  vec4(7.25, 0, -7.25, 1),
  vec4(-7.25, 0, -7.25, 1),
  vec4(-7.25, 0, 7.25, 1)
};

const vec4 colour[2] = {
  vec4(0,1,0,1), // Green
};

const int face[1][4] = {
  {0,1,2,3}
};

void init()
{
  // Load shaders and use the resulting shader program
  GLuint program = InitShader("vshader.glsl", "fshader.glsl");
  glUseProgram(program);
  faceColourLoc = glGetUniformLocation(program, "uFaceColour");
  modelViewLoc = glGetUniformLocation(program, "uModelView");
  projLoc = glGetUniformLocation(program, "uProjection");

  // Initialize the vertex position attribute from the vertex shader
  GLuint loc = glGetAttribLocation( program, "vPosition" );

  // Create a vertex array object for each face
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

    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );
  }
  
  glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
}


//----------------------------------------------------------------------------

mat4 get_projection(mat4 modelview)
{
  GLfloat z1 = 1e10, z2 = -1e10;
  
  for (int i = 0; i < 4; i++) {
    auto p = modelview * point[i];
    z1 = min(z1, -p.z);
    z2 = max(z2, -p.z);
  }

  GLfloat nearPlane, farPlane;

  if (use_perspective) {
    nearPlane = z1 - 0.01;
    farPlane = z2 + 0.01;
    return Perspective(120, 1.0, nearPlane, farPlane);
  } else {
    nearPlane = z1 - 0.5;
    farPlane = z2 + 0.5;
    return Ortho(-1.0, 1.0, -1.0, 1.0, nearPlane, farPlane);
  }
}

void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  mat4 rotate = RotateX(theta_x) * RotateY(theta_y) * RotateZ(theta_z);
  mat4 model = Translate(pos) * rotate * Scale(scale);

  GLfloat eye_x = camera_radius * cos(camera_theta);
  GLfloat eye_y = camera_radius * sin(camera_theta);
  vec4 eye(eye_x, eye_y, 0, 1);
  vec4 at(0,-1,0,1);
  vec4 up(0,0,-1,0);
  mat4 view = LookAt(eye, at, up);
  mat4 modelview = view * model;
  glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, modelview);


  mat4 proj = get_projection(modelview);
  glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);
  
  for (int i = 0; i < 1; i++) {
    glUniform4fv(faceColourLoc, 1, colour[i]);
    glBindVertexArray(vao[i]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);    // draw the square
  }
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
    pos -= vec4(0.05, 0, 0, 0);
    break;
  case GLUT_KEY_RIGHT:
    pos += vec4(0.05, 0, 0, 0);
    break;
  case GLUT_KEY_UP:
    pos += vec4(0, 0, 0.05, 0);
    break;
  case GLUT_KEY_DOWN:
    pos -= vec4(0, 0, 0.05, 0);
    break;
  case GLUT_KEY_PAGE_UP:
    scale *= 1.05;
    break;
  case GLUT_KEY_PAGE_DOWN:
    scale *= 1.0/1.05;
    break;
  case GLUT_KEY_HOME:
    theta_x += 0.5;
    break;
  case GLUT_KEY_END:
    theta_y += 0.5;
    break;
  case GLUT_KEY_INSERT:
    theta_z += 0.5;
    break;
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