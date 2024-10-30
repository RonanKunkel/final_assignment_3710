<<<<<<< HEAD
#version 150

in vec4 vPosition;

// uniform means this is the same value for all vertices
uniform vec4 uFaceColour;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
out vec4 vColour;

void main()
{
  gl_Position = uProjection * uView * uModel * vPosition;

  vColour = uFaceColour;
}
=======
#version 150

in vec4 vPosition;

// uniform means this is the same value for all vertices
uniform vec4 uFaceColour;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
out vec4 vColour;

void main()
{
  gl_Position = uProjection * uView * uModel * vPosition;

  vColour = uFaceColour;
}
>>>>>>> f256c73b4ca0ec25bc1e822d451efe14ea4b3990
