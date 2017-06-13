#include "LightHandler.h"

LightHandler::LightHandler()
{
	this->mLightingChanged = false;
}

LightHandler::~LightHandler()
{
	this->mDirLightBuffer->Release();
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
}

void LightHandler::addDirectionalLight(DirectionalLight* light)
{
	this->mDirLights.push_back(light);
	this->mLightingChanged = true;
}

void LightHandler::removeDirectionalLight(DirectionalLight* light)
{
}

void LightHandler::setConstantBuffer(ID3D11DeviceContext* context)
{
	if (mLightingChanged)
	{
		struct Test 
		{
			int nrOfLights;
			int pad, PAD, PAAAD;
			DirectX::SimpleMath::Vector4 dirs[10];
			DirectX::SimpleMath::Vector4 colors[10];
		};
		Test test;
		test.nrOfLights = 0;
		for (int i = 0; i < this->mDirLights.size() && i < 10; i++)
		{
			test.dirs[i] = this->mDirLights[i]->getDir();
			test.colors[i] = this->mDirLights[i]->getColor();
			test.nrOfLights = i + 1;
		}

		D3D11_MAPPED_SUBRESOURCE data;
		context->Map(this->mDirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
		memcpy(data.pData, &test, 4 * sizeof(float) * 21);
		context->Unmap(this->mDirLightBuffer, 0);
		this->mLightingChanged = false;
	}

	context->PSSetConstantBuffers(0, 1, &mDirLightBuffer);
}
