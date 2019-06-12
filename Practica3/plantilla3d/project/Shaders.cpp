
#include "Shaders.h"
#include"../glew/GL/glew.h"
#include"../glm/gtc/type_ptr.hpp"
#include <fstream> 
#include <sstream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexShaderString = readString(vertexPath);
	std::string fragmentShaderString = readString(fragmentPath);

	const char * vertexShaderCode = vertexShaderString.c_str();
	const char * fragmentShaderCode = fragmentShaderString.c_str();

	idShader = glCreateProgram();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	GLint retCode; 
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE) 
	{
		getError(vertexShader);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	GLint retCode2;
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode2);

	if (retCode2 == GL_FALSE)
	{
		getError(fragmentShader);
	}

	glAttachShader(idShader, vertexShader);
	glAttachShader(idShader, fragmentShader);

	glLinkProgram(idShader);

	glGetShaderiv(idShader, GL_LINK_STATUS, &retCode2);
	if (retCode2 == GL_FALSE)
	{
		getError(fragmentShader);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	setupAttribs(false);
}

uint32_t Shader::getId() const
{
	return vertexShader;
}

const char * Shader::getError(uint32_t vertex) const
{
	char errorLog[1024];
	glGetShaderInfoLog(vertex, sizeof(errorLog), NULL, errorLog);
	return errorLog;
}


void Shader::use()
{
	glUseProgram(idShader);
}

void Shader::setupAttribs(bool bThereIsTex)
{
	m_vposLoc =  glGetAttribLocation(idShader, "vpos");
	if (m_vposLoc != -1) {
		glEnableVertexAttribArray(m_vposLoc);
		glVertexAttribPointer(m_vposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));
	}
	if (!bThereIsTex)
	{
		m_vcolorLoc = glGetAttribLocation(idShader, "vcolor");;
		if (m_vcolorLoc != -1) {
			glEnableVertexAttribArray(m_vcolorLoc);
			glVertexAttribPointer(m_vcolorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, color)));
		}
	}
	else
	{
		m_vtextLoc = glGetAttribLocation(idShader, "vtex");
		if (m_vtextLoc != -1) { 
			glEnableVertexAttribArray(m_vtextLoc); 
			glVertexAttribPointer(m_vtextLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_textureCoord))); 
		}
	}
}

int Shader::getLocation(const char * name) 
{
	return glGetUniformLocation(idShader, name);
}

void Shader::setInt(int loc, int val)
{
	glUniform1i(loc, val);
}

void Shader::setFloat(int loc, float val)
{
	glUniform1f(loc, val);
}

void Shader::setVec3(int loc, const glm::vec3 & vec)
{
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setVec4(int loc, const glm::vec4 & vec)
{
	glUniform4f(loc, vec.w, vec.x, vec.y, vec.z);
}

void Shader::setMatrix(int loc, const glm::mat4 & matrix)
{
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
}

int Shader::getMatrix(const char * name)
{
	return glGetUniformLocation(idShader, name);
}


std::string readString(const std::string& filename) 
{ 
	std::ifstream istream(filename.c_str(), std::ios_base::binary);  
	std::stringstream sstream;  sstream << istream.rdbuf();  
	return sstream.str(); 
}