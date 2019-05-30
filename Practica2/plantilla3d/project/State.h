#pragma once
#include "../project/Shaders.h"
#include <iostream>

class State
{
public:
	State() {};
	static std::shared_ptr<Shader> defaultShader; 
	static glm::mat4     projectionMatrix; 
	static glm::mat4     viewMatrix; 
	static glm::mat4     modelMatrix;
};

std::shared_ptr<Shader> State::defaultShader = nullptr;