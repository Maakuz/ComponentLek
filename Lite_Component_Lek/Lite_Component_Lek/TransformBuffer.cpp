#include "TransformBuffer.h"
using namespace DirectX::SimpleMath;

TransformBuffer::TransformBuffer() : Component(ComponentID::transformBuffer)
{
	this->mTransform = Matrix::Identity;
	this->mBuffer = nullptr;
}

TransformBuffer::~TransformBuffer()
{
	if (this->mBuffer)
		this->mBuffer->Release();
}

void TransformBuffer::setupBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(Matrix);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &this->mTransform;

	device->CreateBuffer(&desc, &data, &this->mBuffer);
}

void TransformBuffer::updateBuffer(ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE data;

	context->Map(this->mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	
	memcpy(data.pData, &this->mTransform, sizeof(this->mTransform));

	context->Unmap(this->mBuffer, 0);
}

void TransformBuffer::resetMatrix()
{
	this->mTransform = Matrix::Identity;
}

void TransformBuffer::multiplyCurrent(DirectX::SimpleMath::Matrix toMultiply)
{
	this->mTransform = toMultiply * this->mTransform;
}

ID3D11Buffer* TransformBuffer::getBuffer()
{
	return this->mBuffer;
}
