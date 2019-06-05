#pragma once
#include <iostream>
#include <vector>

class Buffer;
class Shader;

struct MeshMember
{
	std::shared_ptr<Buffer> myBuffer;
	std::shared_ptr<Shader> myShader;
};
//Soy maluma baby
class Mesh
{
public:
	Mesh() { angle = 0; }
	void addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader = nullptr);
	size_t getNumBuffers() const;
	float angle;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	std::vector<MeshMember> mMyMeshes;
	void draw(float deltaTime, float angleRot);
};