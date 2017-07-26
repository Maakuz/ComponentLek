#include "TransformBuffer.h"
using namespace DirectX::SimpleMath;

TransformBuffer::TransformBuffer() : Component(ComponentID::transformBuffer)
{
	this->mTransform = Matrix::Identity;
}

TransformBuffer::~TransformBuffer()
{
	
}

void TransformBuffer::setupBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &this->mTransform;

	this->mBuffer.setupConstantBuffer(sizeof(Matrix), data, true, device);
}

void TransformBuffer::updateBuffer(ID3D11DeviceContext* context)
{
	this->mBuffer.updateBuffer(sizeof(this->mTransform), &this->mTransform, context);
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
	return this->mBuffer.getBuffer();
}
