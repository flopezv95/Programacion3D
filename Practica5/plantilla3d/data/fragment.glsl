uniform sampler2D texSampler; 
varying vec2 ftex; 
varying vec4 fcolor;

uniform int useTexture; 

void main() 
{ 
	if (useTexture == 1)
	{
		gl_FragColor = texture2D(texSampler, ftex); 
	}
	else
	{
		gl_FragColor = fcolor; 
	}
}