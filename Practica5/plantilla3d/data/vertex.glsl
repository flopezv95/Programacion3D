uniform mat4 mvp;
uniform mat4 model;
uniform mat4 view; 
uniform mat4 projection;

attribute vec3 vpos; 
attribute vec3 vnormal; 
attribute vec4 vcolor; 
attribute vec2 vtex; 

varying vec4 FragPosLightSpace;
varying vec4 fcolor;
varying vec2 TexCoords;
varying vec3 FragPos;
varying vec3 Normal;

void main() { 
	FragPos = vec3(model * vec4(vpos, 1.0)); 
	gl_Position = mvp * vec4(vpos, 1); 
	fcolor = vcolor; 
	TexCoords = vtex; 
	Normal = mat3(transpose(inverse(model))) * vnormal; 
}