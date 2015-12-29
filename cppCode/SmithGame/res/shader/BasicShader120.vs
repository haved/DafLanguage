#version 120

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

uniform mat4 modelspaceMatrix;
uniform mat4 MVP;
uniform vec4 color;

out vec4 vertexColor0;
out vec3 vertexNormal0;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    vertexColor0 = vec4(vertexColor, 1) * color;
    vertexNormal0 = normalize((  modelspaceMatrix*vec4(vertexNormal, 0)  ).xyz);
}
