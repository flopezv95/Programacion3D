
#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"
#include "Buffer.h"
#include "State.h"
#include "Material.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../lib/tinyobjloader/tiny_obj_loader.h" 



std::shared_ptr<Mesh> Mesh::load(const char * filename, const std::shared_ptr<Shader>& shader)
{
	Mesh* retMesh = new Mesh;
	if (shader)
	{
		retMesh->mShader = shader;
	}
	else
	{
		retMesh->mShader = State::defaultShader;
	}
	tinyobj::attrib_t attrib;  
	std::vector<tinyobj::shape_t> shapes; 
	std::vector<tinyobj::material_t> materials; 
	std::string warn, err;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename))
	{ 
		throw std::runtime_error(warn + err); 
	}

	for (const auto& shape : shapes) 
	{ 
		for (const auto& index : shape.mesh.indices) 
		{ 
			Vertex vertexAux; 
			vertexAux.position.x = attrib.vertices[3 * index.vertex_index + 0];    
			vertexAux.position.y = attrib.vertices[3 * index.vertex_index + 1];    
			vertexAux.position.z = attrib.vertices[3 * index.vertex_index + 2];    
			vertexAux.color.r = 1;    
			vertexAux.color.g = 1;    
			vertexAux.color.b = 1;    
			vertexAux.m_textureCoord.x = attrib.texcoords[2 * index.texcoord_index + 0];
			vertexAux.m_textureCoord.y = attrib.texcoords[2 * index.texcoord_index + 1];
			retMesh->mVertexArray.push_back(vertexAux);
			retMesh->mIndexArray.push_back(retMesh->mIndexArray.size());
		} 
	}


	return std::shared_ptr<Mesh>(retMesh);
}

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

std::shared_ptr<Shader>& Mesh::getShader()
{
	return mShader;
}

std::vector<Vertex> Mesh::getVertex()
{
	return mVertexArray;
}

std::vector<unsigned int> Mesh::getIndex()
{
	return mIndexArray;
}

void Mesh::draw(float deltaTime,float angleRot, float rotateInTime)
{
	for (MeshMember myElement : mMyMeshes)
	{
		myElement.myMaterial->prepare(deltaTime, angleRot, rotateInTime);

		myElement.myBuffer->draw(myElement.myMaterial->getShader());
	}
}
