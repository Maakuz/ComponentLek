#include "EasyBuffer.h"

EasyBuffer::EasyBuffer()
{
}

EasyBuffer::~EasyBuffer()
{
	this->mBuffer->Release();
}

bool EasyBuffer::setupConstantBuffer(UINT size, D3D11_SUBRESOURCE_DATA& data, bool isDynamic, ID3D11Device* device)
{
	this->mIsDynamic = isDynamic;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;

	if (isDynamic)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mBuffer);
	if (FAILED(hr))
		return false;
}

bool EasyBuffer::setupVertexBuffer(UINT size, D3D11_SUBRESOURCE_DATA& data, bool isDynamic, ID3D11Device* device)
{
	this->mIsDynamic = isDynamic;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;

	if (isDynamic)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mBuffer);
	if (FAILED(hr))
		return false; 
}

void EasyBuffer::updateBuffer(UINT size, void* toCopy, ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE data;

	context->Map(this->mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	memcpy(data.pData, toCopy, size);

	context->Unmap(this->mBuffer, 0);
}

ID3D11Buffer* EasyBuffer::getBuffer()
{
	return this->mBuffer;
}
