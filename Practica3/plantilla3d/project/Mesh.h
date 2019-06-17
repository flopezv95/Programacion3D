#pragma once
#include <iostream>
#include <vector>

class Buffer;
class Material;

struct MeshMember
{
	std::shared_ptr<Buffer> myBuffer;
	Material* myMaterial;
};
//Soy maluma baby
class Mesh
{
public:
	Mesh() { angle = 0; }
	void addBuffer(const std::shared_ptr<Buffer>& buffer, Material& material);
	size_t getNumBuffers() const;
	float angle;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	const Material& getMaterial(size_t index) const; 
	Material& getMaterial(size_t index);
	std::vector<MeshMember> mMyMeshes;
	void draw(float deltaTime, float angleRot, float rotateInTime = false);
};