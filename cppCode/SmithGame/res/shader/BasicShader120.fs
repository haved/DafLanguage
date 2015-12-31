#version 120

varying vec4 vertexColor0;
varying vec3 vertexNormal0;

void main(){
    gl_FragColor = vec4(vertexColor0.xyz * (dot(vertexNormal0, vec3(0, 0, 1))*0.5+0.5), vertexColor0.w);
}
