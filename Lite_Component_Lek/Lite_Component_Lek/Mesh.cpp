#include "Mesh.h"

Mesh::Mesh() : Component(ComponentID::mesh)
{
	
}

Mesh::~Mesh()
{
	
}

bool Mesh::loadMesh(std::vector<Vertex> vertices, ID3D11Device* device)
{
	UINT size = sizeof(Vertex) * vertices.size();

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &vertices[0];

	this->mNrOfVertices = vertices.size();

	return this->mVertexBuffer.setupVertexBuffer(size, data, false, device);
}

ID3D11Buffer* Mesh::getBuffer()
{
	return this->mVertexBuffer.getBuffer();
}

int Mesh::getNrOfVertices() const
{
	return this->mNrOfVertices;
}
