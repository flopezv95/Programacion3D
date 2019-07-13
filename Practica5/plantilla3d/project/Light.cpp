#include "Light.h"

TType Light::getType() const
{
	return m_myType;
}

void Light::setType(TType type)
{
	m_myType = type;
}

const glm::vec3 & Light::getColor() const
{
	return m_color;
}

void Light::setColor(const glm::vec3 & color)
{
	m_color = color;
}

float Light::getLinearAttenuation() const
{
	return m_linearAttenuation;
}

void Light::setLinearAttenuation(float att)
{
	m_linearAttenuation = att;
}

void Light::prepare(int index, std::shared_ptr<Shader>& shader) const
{
	//TODO: TRY TO UNDERSTAND WHAT PUT HERE
}
