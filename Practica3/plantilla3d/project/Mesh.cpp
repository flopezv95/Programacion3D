
#include "Mesh.h"
#include "Buffer.h"
#include "State.h"
#include "Material.h"
#include "../glm/gtc/matrix_transform.hpp"


void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, Material& material)
{
	MeshMember tempMesh;
	if (buffer != nullptr)
	{
		tempMesh.myBuffer = buffer;
	}
	tempMesh.myMaterial = &material;

	mMyMeshes.push_back(tempMesh);
}

size_t Mesh::getNumBuffers() const
{
	return mMyMeshes.size();
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	return mMyMeshes[index].myBuffer;
}

const Material & Mesh::getMaterial(size_t index) const
{
	return *mMyMeshes[index].myMaterial;
}

Material & Mesh::getMaterial(size_t index)
{
	return *mMyMeshes[index].myMaterial;
}

void Mesh::draw(float deltaTime,float angleRot)
{
	for (MeshMember myElement : mMyMeshes)
	{
		myElement.myMaterial->prepare(deltaTime, angleRot);

		myElement.myBuffer->draw(myElement.myMaterial->getShader());
	}
}
