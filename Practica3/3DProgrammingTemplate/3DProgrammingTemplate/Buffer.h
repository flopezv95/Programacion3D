#pragma once
#include <iostream>
#include <array>
#include <vector>
#include "Shaders.h"

class Vertex;

class Buffer
{
public:
	Buffer(std::vector<Vertex> myVertex, std::vector<GLuint> indices);
	void draw(Shader* shader);
private:
	std::array<uint32_t, 2>m_ids;

    GLuint m_VAO, m_VBO, m_IBO;
    
    std::vector<unsigned int> m_indices;

};
