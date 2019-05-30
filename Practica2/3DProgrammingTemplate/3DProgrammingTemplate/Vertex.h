#pragma once

#include <glm/gtc/type_ptr.hpp>

/* ESTA VAINA NO SIRVE!
class Vertex
{
public:
	Vertex(glm::vec3 vertex, glm::vec3 color);
	~Vertex() {};
	void SetPosition(float pX, float pY, float pZ);
	glm::vec3 GetVertex() { return m_myVector; }
	glm::vec3 m_myVector;
	glm::vec3 m_myVectorColor;
};
*/


struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};
