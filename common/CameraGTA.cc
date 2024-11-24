#include "CameraGTA.h"

CameraGTA::CameraGTA(GLuint viewLoc, GLuint projLoc,
	       vec4 eye, vec4 at, vec4 up,
	       int oleft, int oright, int obot, int otop, int oznear,
	       int ozfar)
  : view_loc(viewLoc), proj_loc(projLoc), eye_pos(eye), at_pos(at), up_dir(up)
{
//   proj_mat = Ortho(oleft, oright, obot, otop, oznear, ozfar);
  proj_mat = Perspective(120, 1.0, 0.5, 20);
}

CameraGTA::~CameraGTA() {}

CameraGTA* CameraGTA::createGTACamera(GLuint viewLoc, GLuint projLoc) {
    vec4 eye(0, 10, 15, 1);   // Camera position
    vec4 at(0, 0, 0, 1);      // Look-at point
    vec4 up(0, 1, 0, 0);      // Up direction
    
    return new CameraGTA(viewLoc, projLoc, eye, at, up, -10, 10, -10, 10, -1, 100);
}

void CameraGTA::moveEye(GLfloat dx, GLfloat dy, GLfloat dz)
{
  eye_pos.x += dx;
  eye_pos.y += dy;
  eye_pos.z += dz;
}

void CameraGTA::sendToShader() const
{
  mat4 view_mat = LookAt(eye_pos, at_pos, up_dir);
  glUniformMatrix4fv(view_loc, 1, GL_TRUE, view_mat);
  glUniformMatrix4fv(proj_loc, 1, GL_TRUE, proj_mat);
}