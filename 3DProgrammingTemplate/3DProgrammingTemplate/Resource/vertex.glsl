#version 400 core
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vcolor;

uniform mat4 mvp;
out vec3 fcolor;

void main() {
    gl_Position = vec4(vpos, 1);
    fcolor = vcolor;
}
