
#include <GL/glew.h>
#include "Buffer.h"
#include "Vertex.h"
#include "Shaders.h"

Buffer::Buffer(std::vector<Vertex> myVertex, std::vector<unsigned int> indices)
{
	if (myVertex.size() > 0 && indices.size() > 0)
	{
		m_indices = indices;

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, myVertex.size() * sizeof(Vertex), &myVertex[0], GL_STATIC_DRAW);

	}
	
}

void Buffer::draw(std::shared_ptr<Shader> shader)
{
	 glBindVertexArray(m_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    (*shader).setupAttribs();
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
