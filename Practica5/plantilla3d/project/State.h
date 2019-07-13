#pragma once
#include "../project/Shaders.h"
#include "Light.h"
#include <iostream>
#include <vector>

class State
{
public:
	State() {};
	static std::shared_ptr<Shader> defaultShader; 
	static glm::mat4     projectionMatrix; 
	static glm::mat4     viewMatrix; 
	static glm::mat4     modelMatrix;
	static std::vector<std::shared_ptr<Light>> lights; 
	static glm::vec3      ambient;
};

