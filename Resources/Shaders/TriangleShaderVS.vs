attribute vec3 a_posL;
attribute vec3 a_color;
varying vec4 v_color;
uniform mat4 u_mvpMatrix;
attribute vec2 a_texCoord;  
varying vec2 v_texCoord;

void main()
{

gl_Position = u_mvpMatrix*vec4(a_posL, 1.0);
v_color = vec4(a_color, 1.0);
v_texCoord = a_texCoord;
} 
   