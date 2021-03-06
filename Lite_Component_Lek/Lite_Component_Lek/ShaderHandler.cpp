#include "ShaderHandler.h"

ShaderHandler::ShaderHandler()
{
}

ShaderHandler::~ShaderHandler()
{
	for (int i = 0; i < this->mGeometryShaders.size(); i++)
	{
		if (this->mGeometryShaders[i])
			this->mGeometryShaders[i]->Release();
	}

	for (int i = 0; i < this->mVertexShaders.size(); i++)
	{
		if (this->mVertexShaders[i])
			this->mVertexShaders[i]->Release();
		
		if (this->mInputLayout[i])
			this->mInputLayout[i]->Release();
	}

	for (int i = 0; i < this->mPixelShaders.size(); i++)
	{
		if (this->mPixelShaders[i])
			this->mPixelShaders[i]->Release();
	}

	for (int i = 0; i < this->mComputeShaders.size(); i++)
	{
		if (this->mComputeShaders[i])
			this->mComputeShaders[i]->Release();
	}
}

int ShaderHandler::setupVertexShader(ID3D11Device* device, wchar_t* name, char* entrypoint, D3D11_INPUT_ELEMENT_DESC * desc, UINT nrOfElements)
{
	ID3DBlob* blob = nullptr;
	HRESULT hr;
	int returnVal = -1;

	hr = D3DCompileFromFile(name, nullptr, nullptr, entrypoint, "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr))
	{
		ID3D11VertexShader* vertexShader;
		hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);

		if (SUCCEEDED(hr))
		{
			ID3D11InputLayout* layout;
			device->CreateInputLayout(desc, nrOfElements, blob->GetBufferPointer(), blob->GetBufferSize(), &layout);

			if (SUCCEEDED(hr))
			{
				this->mVertexShaders.push_back(vertexShader);
				this->mInputLayout.push_back(layout);
				blob->Release();


				returnVal = this->mVertexShaders.size() - 1;
			}
		}
	}

	if (blob)
		blob->Release();

	return returnVal;
}

int ShaderHandler::setupGeometryShader(ID3D11Device * device, wchar_t * name, char * entrypoint)
{
	ID3DBlob* blob = nullptr;
	HRESULT hr;
	int returnVal = -1;
	//REMOVE DEBUG WHEN DONE
	hr = D3DCompileFromFile(
		name, nullptr, nullptr, entrypoint, "gs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr))
	{
		ID3D11GeometryShader* geometryShader;
		hr = device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &geometryShader);

		if (SUCCEEDED(hr))
		{
			this->mGeometryShaders.push_back(geometryShader);
			blob->Release();


			returnVal = this->mGeometryShaders.size() - 1;
		}

	}

	if (blob)
		blob->Release();

	return returnVal;
}

int ShaderHandler::setupPixelShader(ID3D11Device* device, wchar_t* name, char* entrypoint)
{
	ID3DBlob* blob = nullptr;
	HRESULT hr;
	int returnVal = -1;
	//REMOVE DEBUG WHEN DONE
	hr = D3DCompileFromFile(
		name, nullptr, nullptr, entrypoint, "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr))
	{
		ID3D11PixelShader* pixelShader;
		hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);

		if (SUCCEEDED(hr))
		{
			this->mPixelShaders.push_back(pixelShader);
			blob->Release();


			returnVal = this->mPixelShaders.size() - 1;
		}
		
	}

	if (blob)
		blob->Release();

	return returnVal;
}

int ShaderHandler::setupComputeShader(ID3D11Device* device, wchar_t * name, char * entrypoint)
{
	ID3DBlob* blob = nullptr;
	HRESULT hr;
	int returnVal = -1;
	//REMOVE DEBUG WHEN DONE
	hr = D3DCompileFromFile(
		name, nullptr, nullptr, entrypoint, "cs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &blob, nullptr);

	if (SUCCEEDED(hr))
	{
		ID3D11ComputeShader* computeShader;
		hr = device->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &computeShader);

		if (SUCCEEDED(hr))
		{
			this->mComputeShaders.push_back(computeShader);
			blob->Release();


			returnVal = this->mComputeShaders.size() - 1;
		}

	}

	if (blob)
		blob->Release();

	return returnVal;
}

void ShaderHandler::setShaders(int vs, int gs, int ps, ID3D11DeviceContext* context)
{
	context->VSSetShader(vs == -1 ? nullptr : this->mVertexShaders[vs], nullptr, 0);
	context->IASetInputLayout(vs == -1 ? nullptr : this->mInputLayout[vs]);
	context->GSSetShader(gs == -1 ? nullptr : this->mGeometryShaders[gs], nullptr, 0);
	context->PSSetShader(ps == -1 ? nullptr : this->mPixelShaders[ps], nullptr, 0);
}

void ShaderHandler::setVS(int vs, ID3D11DeviceContext* context)
{
	context->VSSetShader(vs == -1 ? nullptr : this->mVertexShaders[vs], nullptr, 0);
	context->IASetInputLayout(vs == -1 ? nullptr : this->mInputLayout[vs]);
}

void ShaderHandler::setGS(int gs, ID3D11DeviceContext* context)
{
	context->GSSetShader(gs == -1 ? nullptr : this->mGeometryShaders[gs], nullptr, 0);
}

void ShaderHandler::setPS(int ps, ID3D11DeviceContext* context)
{
	context->PSSetShader(ps == -1 ? nullptr : this->mPixelShaders[ps], nullptr, 0);
}

void ShaderHandler::setCS(int cs, ID3D11DeviceContext* context)
{
	context->CSSetShader(cs == -1 ? nullptr : this->mComputeShaders[cs], nullptr, 0);
}
