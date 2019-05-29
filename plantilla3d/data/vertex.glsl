uniform mat4 mvp;
attribute vec3 vpos;
attribute vec4 vcolor; 
varying vec4 fcolor;

void main() {
    gl_Position = mvp * vec4(vpos, 1);
	fcolor = vcolor; 
}