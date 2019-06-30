#pragma once
#include <iostream>
#include <vector>
#include "Vertex.h"

class Buffer;
class Material;
class Shader;

struct MeshMember
{
	std::shared_ptr<Buffer> myBuffer;
	Material* myMaterial;
};

class Mesh
{
public:
	Mesh() { angle = 0; }
	static std::shared_ptr<Mesh> load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);
	void addBuffer(const std::shared_ptr<Buffer>& buffer, Material& material);
	size_t getNumBuffers() const;
	float angle;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	const Material& getMaterial(size_t index) const; 
	Material& getMaterial(size_t index);
	std::vector<MeshMember> mMyMeshes;
	std::shared_ptr<Shader>& getShader();
	std::vector<Vertex> getVertex();
	std::vector<unsigned int> getIndex();
	void draw(float deltaTime, float angleRot, float rotateInTime = false);

private:
	std::shared_ptr<Shader> mShader;
	std::vector<unsigned int> mIndexArray;
	std::vector<Vertex> mVertexArray;
	std::string mTextureName;
};