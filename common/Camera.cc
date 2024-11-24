#include "Camera.h"

Camera::Camera(GLuint viewLoc, GLuint projLoc,
	       vec4 eye, vec4 at, vec4 up,
	       int oleft, int oright, int obot, int otop, int oznear,
	       int ozfar)
  : view_loc(viewLoc), proj_loc(projLoc), eye_pos(eye), at_pos(at), up_dir(up)
{
  proj_mat = Ortho(oleft, oright, obot, otop, oznear, ozfar);
  // proj_mat = Perspective(120, 1.0, 0.5, 20);
}

Camera::~Camera() {}

Camera* Camera::createOrthoCamera(GLuint viewLoc, GLuint projLoc) {
    // top down
    vec4 eye(0, 15, 5, 1);
    vec4 at(0, 0, 0, 1);
    vec4 up(0, 5, -5, 0);
    
    return new Camera(viewLoc, projLoc, eye, at, up, -10, 10, -10, 10, -1, 100);
}

void Camera::moveEye(GLfloat dx, GLfloat dy, GLfloat dz)
{
  eye_pos.x += dx;
  eye_pos.y += dy;
  eye_pos.z += dz;
}

void Camera::sendToShader() const
{
  mat4 view_mat = LookAt(eye_pos, at_pos, up_dir);
  glUniformMatrix4fv(view_loc, 1, GL_TRUE, view_mat);
  glUniformMatrix4fv(proj_loc, 1, GL_TRUE, proj_mat);
}
