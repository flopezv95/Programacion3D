
#include "Vertex.h"

Vertex::Vertex(glm::vec3 vertex, glm::vec3 color)
{
	m_myVector = vertex;
	m_myVectorColor = color;
}

void Vertex::SetPosition(float pX, float pY, float pZ)
{
	m_myVector = glm::vec3(pX, pY, pZ);
}
