#include "LightHandler.h"

LightHandler::LightHandler()
{
	this->mDirLightChanged = false;
	this->mPointLightChanged = false;
}

LightHandler::~LightHandler()
{
	this->mDirLightBuffer->Release();
	this->mPointLightBuffer->Release();
}

void LightHandler::setupLightBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = 4 * sizeof(float) * 21;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	device->CreateBuffer(&desc, NULL, &this->mDirLightBuffer);

	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = 4 * sizeof(float) * 31 + 40 * 4;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	device->CreateBuffer(&desc, NULL, &this->mPointLightBuffer);
}

void LightHandler::addDirectionalLight(DirectionalLight* light)
{
	this->mDirLights.push_back(light);
	this->mDirLightChanged = true;
}

void LightHandler::addPointLight(PointLight* light)
{
	this->mPointLights.push_back(light);
	this->mPointLightChanged = true;
}

void LightHandler::removeDirectionalLight(DirectionalLight* light)
{
}

void LightHandler::setConstantBuffer(ID3D11DeviceContext* context)
{
	if (mDirLightChanged)
	{
		struct DirLightStruct 
		{
			int nrOfLights;
			int pad, PAD, PAAAD;
			DirectX::SimpleMath::Vector4 dirs[10];
			DirectX::SimpleMath::Vector4 colors[10];
		};
		DirLightStruct light;
		light.nrOfLights = 0;
		for (int i = 0; i < this->mDirLights.size() && i < 10; i++)
		{
			light.dirs[i] = this->mDirLights[i]->getDir();
			light.colors[i] = this->mDirLights[i]->getColor();
			light.nrOfLights = i + 1;
		}

		D3D11_MAPPED_SUBRESOURCE data;
		context->Map(this->mDirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		memcpy(data.pData, &light, 4 * sizeof(float) * 21);
		context->Unmap(this->mDirLightBuffer, 0);
		this->mDirLightChanged = false;
	}

	if (mPointLightChanged)
	{
		struct PointLightStruct
		{
			int nrOfLights;
			int pad, PAD, PAAAD;
			DirectX::SimpleMath::Vector4 positions[30];
			float radiuses[30];
		};
		PointLightStruct light;
		light.nrOfLights = 0;
		for (int i = 0; i < this->mPointLights.size() && i < 10; i++)
		{
			light.positions[i] = DirectX::SimpleMath::Vector4(this->mPointLights[i]->getPos());
			light.radiuses[i] = this->mPointLights[i]->getRadius();
			light.nrOfLights = i + 1;
		}

		D3D11_MAPPED_SUBRESOURCE data;
		context->Map(this->mPointLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		memcpy(data.pData, &light, 4 * sizeof(float) * 31 + 40 * 4);
		context->Unmap(this->mPointLightBuffer, 0);
		this->mDirLightChanged = false;
	}

	context->PSSetConstantBuffers(0, 1, &mDirLightBuffer);
	context->PSSetConstantBuffers(1, 1, &mPointLightBuffer);
}
