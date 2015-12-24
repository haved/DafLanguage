#version 330 core

in vec4 vertexColor0;
in vec3 vertexNormal0;

out vec4 fragColor;

void main(){
    fragColor = vec4(vertexColor0.xyz * (dot(vertexNormal0, vec3(0, 0, 1)) + 0.5), vertexColor0.w);
}
