
#include "Mesh.h"
#include "Buffer.h"
#include "State.h"
#include "../glm/gtc/matrix_transform.hpp"


void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader)
{
	MeshMember tempMesh;
	if (buffer != nullptr)
	{
		tempMesh.myBuffer = buffer;
	}
	if (shader == nullptr)
	{
		tempMesh.myShader = State::defaultShader;
	}
	else
	{
		tempMesh.myShader = shader;
	}

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

void Mesh::draw(float deltaTime,float angleRot)
{
	for (MeshMember myElement : mMyMeshes)
	{
		myElement.myShader->use();

		angle += (angleRot * deltaTime);
		glm::mat4 proj = State::projectionMatrix;
		glm::mat4 view = State::viewMatrix;
		glm::mat4 model = State::modelMatrix;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		State::defaultShader->setMatrix(State::defaultShader->getLocation("mvp"), proj*view*model);

		myElement.myBuffer->draw(myElement.myShader);
	}
}
