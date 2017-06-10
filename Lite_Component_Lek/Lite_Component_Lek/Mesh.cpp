#include "Mesh.h"

Mesh::Mesh() : Component(ComponentID::mesh)
{
	this->mVertexBuffer = nullptr;
}

Mesh::~Mesh()
{
	if (this->mVertexBuffer)
		this->mVertexBuffer->Release();
}

bool Mesh::loadMesh(std::vector<Vertex> vertices, ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(Vertex) * vertices.size();
	desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &vertices[0];

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mVertexBuffer);
	if (FAILED(hr))
		return false;

	return true;
}

ID3D11Buffer* Mesh::getBuffer()
{
	return this->mVertexBuffer;
}
