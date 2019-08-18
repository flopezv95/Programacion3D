uniform sampler2D texSampler;
uniform sampler2D diffuse;

struct Material { 
sampler2D diffuse; 
sampler2D specular; 
float shininess;
vec3 ambientColor; 
vec3 diffuseColor; 
vec3 specularColor; 
};
struct DirLight{ 
vec3 direction;
vec3 ambient; 
vec3 diffuse; 
vec3 specular;
};

varying vec2 TexCoords; 
varying vec3 FragPos;
varying vec3 Normal;
varying vec4 fcolor;

uniform int useTexture;
uniform vec3 viewPos; 
uniform DirLight dirLight; 
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main() 
{ 
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	gl_FragColor = vec4(result, 1.0); 
	
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) 
{ 
	vec3 lightDir = normalize(-light.direction); 
	// diffuse shading 
	float diff = max(dot(normal, lightDir), 0.0); 
	// specular shading 
	vec3 reflectDir = reflect(-lightDir, normal); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
	// combine results 
	vec3 ambient  = light.ambient * material.ambientColor; 
	vec3 diffuse = light.diffuse * diff *  material.diffuseColor; 
	vec3 specular = light.specular * spec *  material.specularColor; 
	if (useTexture == 1) 
	{ 
		ambient  = ambient  * vec3(texture(material.diffuse, TexCoords)); 
		diffuse  = diffuse  * vec3(texture(material.diffuse, TexCoords)); 
		specular = specular * vec3(texture(material.specular, TexCoords)); 
	} 
	return (ambient + diffuse + specular);
}