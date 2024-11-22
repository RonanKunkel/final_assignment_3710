#include <Angel.h>

#ifndef CAMERA_H
#define CAMERA_H

using namespace std;

class Camera
{
public:
  Camera(GLuint viewLoc, GLuint projLoc,
	 vec4 eye, vec4 at, vec4 up,
	 int oleft, int oright, int obot, int otop, int oznear,
	 int ozfar);
  ~Camera();

  void moveEye(GLfloat dx, GLfloat dy, GLfloat dz);

  void sendToShader() const;
  

private:
  GLuint view_loc, proj_loc;
  vec4 eye_pos, at_pos, up_dir;
  mat4 proj_mat;
};

#endif
