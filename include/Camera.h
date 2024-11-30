#include <Angel.h>

#ifndef CAMERA_H
#define CAMERA_H

using namespace std;

class Camera {
public:
 // Constructor for camera
 Camera(GLuint viewLoc, GLuint projLoc,
  vec4 eye, vec4 at, vec4 up,
  int oleft, int oright, int obot, int otop, int oznear,
  int ozfar);
 ~Camera(); 
 // functions for creating the two different types of cameras
 static Camera* createPerspectiveCamera(GLuint viewLoc, GLuint projLoc);
 // eye fucntions for movement of eye
 void moveEye(GLfloat dx, GLfloat dy, GLfloat dz);
 void setView(vec4 eye, vec4 at, vec4 up);
 void setProjection(mat4 projection);
 void sendToShader() const;
 // functions for creating the two different types of cameras
 void setDefaultView(vec4 car_position);
 void setOverheadView(vec4 car_position);
 void setSideView(vec4 car_position); 
private:
 // variables for creation and movement of cameras
 GLuint view_loc, proj_loc;
 vec4 eye_pos, at_pos, up_dir;
 mat4 view_mat, proj_mat;
};

#endif
