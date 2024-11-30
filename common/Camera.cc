#include "Camera.h"

// camera constructor that takes in eye, at, and up as params to use to set cameras
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

// creates the camera for the perspective view and sends to shader
Camera* Camera::createPerspectiveCamera(GLuint viewLoc, GLuint projLoc) {
  vec4 eye = vec4(0.0, 0.0, 5.0, 1.0);
  vec4 at = vec4(0.0, 0.0, 0.0, 1.0);
  vec4 up = vec4(0.0, 1.0, 0.0, 0.0);
  Camera* cam = new Camera(viewLoc, projLoc, eye, at, up, 0,0,0,0,0,0);
  cam->proj_mat = Perspective(45.0, 1.0, 0.1, 100.0);
  cam->sendToShader();
  return cam;
}

// sets view and sends to shader
void Camera::setView(vec4 eye, vec4 at, vec4 up) {
  eye_pos = eye;
  at_pos = at;
  up_dir = up;
  view_mat = LookAt(eye_pos, at_pos, up_dir);
  sendToShader();
}

// sets projection and sends to shader
void Camera::setProjection(mat4 projection) {
  proj_mat = projection;
  sendToShader();
}

// moves eyes to different spot in world using xyz coords
void Camera::moveEye(GLfloat dx, GLfloat dy, GLfloat dz) {
  eye_pos.x += dx;
  eye_pos.y += dy;
  eye_pos.z += dz;
  view_mat = LookAt(eye_pos, at_pos, up_dir);
  sendToShader();
}

void Camera::sendToShader() const {
  glUniformMatrix4fv(view_loc, 1, GL_TRUE, view_mat);
  glUniformMatrix4fv(proj_loc, 1, GL_TRUE, proj_mat);
}

// set params to be the default view (behind and above)
void Camera::setDefaultView(vec4 car_position) {
  vec4 eye = vec4(car_position.x, car_position.y + 0.6, car_position.z + 1.5, 1.0);
  vec4 at = car_position;
  vec4 up = vec4(0.0, 1.0, 0.0, 0.0);
  setView(eye, at, up);
}

// set params to be overhead the plane (top down)
void Camera::setOverheadView(vec4 car_position) {
  vec4 eye = vec4(car_position.x, car_position.y + 5.0, car_position.z, 1.0);
  vec4 at = car_position;
  vec4 up = vec4(0.0, 0.0, -1.0, 0.0);
  setView(eye, at, up);
}

// set params to be side view to see wheels and car
void Camera::setSideView(vec4 car_position) {
  vec4 eye = vec4(car_position.x + 0.6, car_position.y + 0.6, car_position.z, 1.0);
  vec4 at = car_position;
  vec4 up = vec4(0.0, 1.0, 0.0, 0.0);
  setView(eye, at, up);
}
