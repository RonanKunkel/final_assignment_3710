#include <Angel.h>

#ifndef CAMERAGTA_H
#define CAMERAGTA_H

using namespace std;

class CameraGTA
{
public:
  CameraGTA(GLuint viewLoc, GLuint projLoc,
	 vec4 eye, vec4 at, vec4 up,
	 int oleft, int oright, int obot, int otop, int oznear,
	 int ozfar);
  ~CameraGTA();
  static CameraGTA* createGTACamera(GLuint viewLoc, GLuint projLoc);
  void moveEye(GLfloat dx, GLfloat dy, GLfloat dz);
  void sendToShader() const;
  

private:
  GLuint view_loc, proj_loc;
  vec4 eye_pos, at_pos, up_dir;
  mat4 proj_mat;
};

#endif
