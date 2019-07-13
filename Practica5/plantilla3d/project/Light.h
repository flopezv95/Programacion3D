#pragma once
#include <iostream>
#include"../glew/GL/glew.h"
#include "../glm/glm.hpp"

class Shader;

enum TType
{
	EDIRECTIONAL,
	EPOINT,
};

class Light
{
public:
	TType   getType() const; 
	void   setType(TType type); 
	const glm::vec3& getColor() const; 
	void   setColor(const glm::vec3& color); 
	float   getLinearAttenuation() const; 
	void   setLinearAttenuation(float att); 
	void   prepare(int index, std::shared_ptr<Shader>& shader) const;
private:
	TType m_myType;
	glm::vec3 m_color;
	float m_linearAttenuation;
};
