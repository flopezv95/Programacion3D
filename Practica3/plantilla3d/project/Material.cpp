#include "Material.h"
#include "State.h"
#include "Texture.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "Shaders.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
{
	if (shader)
	{
		myShader = shader;
	}
	else
	{
		myShader = State::defaultShader;
	}
	if (tex)
	{
		myTexture = tex;
		bUseTexture = true;
	}
	else
	{
		bUseTexture = false;
	}
}

const std::shared_ptr<Shader>& Material::getShader() const
{
	return myShader;
}

std::shared_ptr<Shader>& Material::getShader()
{
	return myShader;
}

void Material::setShader(const std::shared_ptr<Shader>& shader)
{
	myShader = shader;
}

const std::shared_ptr<Texture>& Material::getTexture() const
{
	if (bUseTexture)
	{
		return myTexture;
	}
	else
	{
		return nullptr;
	}
}

void Material::setTexture(const std::shared_ptr<Texture>& tex)
{
	myTexture = tex;
}

void Material::prepare(float deltaTime, float angleRot)
{
	myShader->use();

	angle += (angleRot * deltaTime);
	glm::mat4 proj = State::projectionMatrix;
	glm::mat4 view = State::viewMatrix;
	glm::mat4 model = State::modelMatrix;
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	myShader->setMatrix(State::defaultShader->getLocation("mvp"), proj*view*model);
	myShader->setupAttribs(bUseTexture);
	if (bUseTexture)
	{
		myTexture->bind();
		myShader->setInt(myShader->getLocation("texSampler"), 0);
	}
}
