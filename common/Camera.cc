#include "Camera.h"

Camera::Camera(GLuint viewLoc, GLuint projLoc,
	       vec4 eye, vec4 at, vec4 up,
	       int oleft, int oright, int obot, int otop, int oznear,
	       int ozfar)
  : view_loc(viewLoc), proj_loc(projLoc), eye_pos(eye), at_pos(at), up_dir(up)
{
  proj_mat = Ortho(oleft, oright, obot, otop, oznear, ozfar);
  view_mat = LookAt(eye_pos, at_pos, up_dir);
}

Camera::~Camera() {}

Camera* Camera::createOrthoCamera(GLuint viewLoc, GLuint projLoc) {
    // top down
    vec4 eye(0.0, 0.0, 5.0, 1.0);
    vec4 at(0.0, 0.0, 0.0, 1.0);
    vec4 up(0.0, 1.0, 0.0, 0.0);
    
    return new Camera(viewLoc, projLoc, eye, at, up, -10, 10, -10, 10, 0.1, 100.0);
}

Camera* Camera::createPerspectiveCamera(GLuint viewLoc, GLuint projLoc) {
  vec4 eye = vec4(0.0, 0.0, 5.0, 1.0);
  vec4 at = vec4(0.0, 0.0, 0.0, 1.0);
  vec4 up = vec4(0.0, 1.0, 0.0, 0.0);
  Camera* cam = new Camera(viewLoc, projLoc, eye, at, up, 0,0,0,0,0,0);
  cam->proj_mat = Perspective(45.0, 1.0, 0.1, 100.0);
  return cam;
}

void Camera::setView(vec4 eye, vec4 at, vec4 up) {
  eye_pos = eye;
  at_pos = at;
  up_dir = up;
  view_mat = LookAt(eye_pos, at_pos, up_dir);
}

void Camera::setProjection(mat4 projection) {
  proj_mat = projection;
}

void Camera::moveEye(GLfloat dx, GLfloat dy, GLfloat dz) {
  eye_pos.x += dx;
  eye_pos.y += dy;
  eye_pos.z += dz;
  view_mat = LookAt(eye_pos, at_pos, up_dir);
}

void Camera::sendToShader() const {
  mat4 view_mat = LookAt(eye_pos, at_pos, up_dir);
  glUniformMatrix4fv(view_loc, 1, GL_TRUE, view_mat);
  glUniformMatrix4fv(proj_loc, 1, GL_TRUE, proj_mat);
}

void Camera::setDefaultView(vec4 car_position) {
  vec4 eye = vec4(car_position.x, car_position.y + 5.0, car_position.z - 10.0, 1.0);
  vec4 at = car_position;
  vec4 up= vec4(0.0, 0.0, 1.0, 0.0);
  setView(eye, at, up);
}

void Camera::setOverheadView(vec4 car_position) {
  vec4 eye = vec4(car_position.x, car_position.y + 20.0, car_position.z, 1.0);
  vec4 at = car_position;
  vec4 up= vec4(0.0, 0.0, -1.0, 0.0);
  setView(eye, at, up);
}

void Camera::setSideView(vec4 car_position) {
  vec4 eye = vec4(car_position.x + 10.0, car_position.y + 5.0, car_position.z, 1.0);
  vec4 at = car_position;
  vec4 up= vec4(0.0, 1.0, 0.0, 0.0);
  setView(eye, at, up);
}


