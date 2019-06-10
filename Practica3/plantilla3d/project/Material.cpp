#include "Material.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
{
}

const std::shared_ptr<Shader>& Material::getShader() const
{
	// TODO: insert return statement here
}

std::shared_ptr<Shader>& Material::getShader()
{
	// TODO: insert return statement here
}

void Material::setShader(const std::shared_ptr<Shader>& shader)
{
}

const std::shared_ptr<Texture>& Material::getTexture() const
{
	// TODO: insert return statement here
}

void Material::setTexture(const std::shared_ptr<Texture>& tex)
{
}

void Material::prepare()
{
}
