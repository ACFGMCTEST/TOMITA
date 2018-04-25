#version 120
//uniform vec4 Specular;
attribute vec4 indices;
attribute vec4 weights;
uniform mat4 Transforms[155];
uniform mat4 WorldMatrix;
uniform float cnt;
//フラグメントシェーダーに渡す変数
varying vec3 N;//法線ベクトル

//簡単なシェーダープログラムを作りたい
void main(void)
{
  vec4 position = gl_ModelViewMatrix * gl_Vertex;
  vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
  vec3 light = normalize((gl_LightSource[0].position * position.w - gl_LightSource[0].position.w * position).xyz);
 
  float diffuse = max(dot(light, normal), 0.0);
  
  gl_FrontColor = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * diffuse;
  
  gl_Position = ftransform();
}
