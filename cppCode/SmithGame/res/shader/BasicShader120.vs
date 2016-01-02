#version 120

attribute vec3 vertexPosition_modelspace;
attribute vec3 vertexNormal;
attribute vec2 texCoord;
attribute vec3 vertexColor;

uniform mat4 modelspaceMatrix;
uniform mat4 MVP;
uniform vec4 color;

varying vec3 vertexNormal0;
varying vec2 texCoord0;
varying vec4 vertexColor0;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    vertexColor0 = vec4(vertexColor, 1) * color;
    vertexNormal0 = normalize((  modelspaceMatrix*vec4(vertexNormal, 0)  ).xyz);
    texCoord0 = texCoord;
}
