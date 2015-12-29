#version 120

in vec4 vertexColor0;
in vec3 vertexNormal0;

void main(){
    gl_FragColor = vec4(vertexColor0.xyz * (dot(vertexNormal0, vec3(0, 0, 1)) + 0.5), vertexColor0.w);
}
