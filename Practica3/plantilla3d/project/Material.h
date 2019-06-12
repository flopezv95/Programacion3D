#pragma once
#include <iostream>
#include <vector>
#include "../glm/glm.hpp"

class Shader;
class Texture;

class Material
{
public:
	Material(const std::shared_ptr<Texture>& tex = nullptr, const std::shared_ptr<Shader>& shader = nullptr);
	const std::shared_ptr<Shader>& getShader() const;
	std::shared_ptr<Shader>& getShader();
	void setShader(const std::shared_ptr<Shader>& shader);
	const std::shared_ptr<Texture>& getTexture() const;
	void setTexture(const std::shared_ptr<Texture>& tex);
	void prepare(float deltaTime, float angleRot);
private:
	std::shared_ptr<Texture> myTexture;
	std::shared_ptr<Shader> myShader;
	bool bUseTexture;
	float angle;
};