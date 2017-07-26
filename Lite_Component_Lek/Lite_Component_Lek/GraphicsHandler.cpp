#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler()
{
	this->mBackBufferRTV = nullptr;
	this->mContext = nullptr;
	this->mDebugDevice = nullptr;
	this->mDevice = nullptr;
	this->mSwapChain = nullptr;
	this->nullUAV = nullptr;
}

GraphicsHandler::~GraphicsHandler()
{
	this->mBackBufferRTV->Release();
	this->mContext->Release();
	this->mDevice->Release();
	this->mSwapChain->Release();
	this->mDSS->Release();
	this->mDSV->Release();

	this->UAVS[0]->Release();
	this->UAVS[1]->Release();
	this->SRVS[0]->Release();
	this->SRVS[1]->Release();
	this->particleCountBuffer->Release();
	this->IndirectArgsBuffer->Release();


	//this->mDebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	this->mDebugDevice->Release();
}

HRESULT GraphicsHandler::setup3DContent()
{
	DXGI_SWAP_CHAIN_DESC mSwapChainDesc;
	ZeroMemory(&mSwapChainDesc, sizeof(mSwapChainDesc));
	mSwapChainDesc.BufferCount = 1;
	mSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	mSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	mSwapChainDesc.OutputWindow = GetActiveWindow(); //get window from SDL2
	mSwapChainDesc.Windowed = TRUE;

	mSwapChainDesc.SampleDesc.Count = 4;

	D3D_FEATURE_LEVEL test[2];

	test[0] = D3D_FEATURE_LEVEL_11_1;
	test[1] = D3D_FEATURE_LEVEL_11_0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		test, 2, D3D11_SDK_VERSION, &mSwapChainDesc, &mSwapChain, &mDevice,
		nullptr, &mContext
	);

	if (SUCCEEDED(hr)) {
		ID3D11Texture2D* backBuffer = nullptr;
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

		if (SUCCEEDED(hr)) {
			//this->createDepthStencil();

			hr = mDevice->CreateRenderTargetView(backBuffer, nullptr, &mBackBufferRTV);
			backBuffer->Release();

			//Creating debug device
			HRESULT hr = this->mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast <void **>(&mDebugDevice));
			if (FAILED(hr))
			{
				MessageBox(0, L"Debug device creation failed", L"error", MB_OK);
			}
		}
	}

	else
		MessageBox(NULL, L"SWAPCHAIN GICK INTE", L"FASIKEN", SDL_MESSAGEBOX_ERROR);

	return hr;
}

void GraphicsHandler::setupShaders()
{
	D3D11_INPUT_ELEMENT_DESC desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	mEntitySetup.vs = mShaderHandler.setupVertexShader(this->mDevice, L"VertexShader.hlsl", "main", desc, ARRAYSIZE(desc));
	if (mEntitySetup.vs == -1)
		exit(-2);

	mEntitySetup.vsTransform = mShaderHandler.setupVertexShader(this->mDevice, L"VertexShaderTransform.hlsl", "main", desc, ARRAYSIZE(desc));
	if (mEntitySetup.vsTransform == -1)
		exit(-2);

	mEntitySetup.gs = -1;

	mEntitySetup.ps = mShaderHandler.setupPixelShader(this->mDevice, L"PixelShader.hlsl", "main");
	if (mEntitySetup.ps == -1)
		exit(-3);

	mEntitySetup.psLight = mShaderHandler.setupPixelShader(this->mDevice, L"PixelShaderLight.hlsl", "main");
	if (mEntitySetup.psLight == -1)
		exit(-3);


	//Particle shaders
	D3D11_INPUT_ELEMENT_DESC particleDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	mParticleSetup.vs = mShaderHandler.setupVertexShader(this->mDevice, L"ParticleComputeVS.hlsl", "main", particleDesc, ARRAYSIZE(particleDesc));
	if (mParticleSetup.vs == -1)
		exit(-2);

	mParticleSetup.gs = mShaderHandler.setupGeometryShader(this->mDevice, L"ParticleGS.hlsl", "main");
	if (mParticleSetup.gs == -1)
		exit(-4);

	mParticleSetup.ps = mShaderHandler.setupPixelShader(this->mDevice, L"ParticlePS.hlsl", "main");
	if (mParticleSetup.ps == -1)
		exit(-3);

	mParticleCS.updater = mShaderHandler.setupComputeShader(this->mDevice, L"ParticleCS.hlsl", "main");
	if (mParticleCS.updater == -1)
		exit(-5);

	mParticleCS.injector = mShaderHandler.setupComputeShader(this->mDevice, L"ParticleInjector.hlsl", "main");
	if (mParticleCS.injector == -1)
		exit(-5);
}

void GraphicsHandler::setupLightHandler()
{
	this->mLightHandler.setupLightBuffers(this->mDevice);
}

void GraphicsHandler::setupDepthStencil()
{
	D3D11_TEXTURE2D_DESC descTex;
	ZeroMemory(&descTex, sizeof(descTex));
	descTex.ArraySize = descTex.MipLevels = 1;
	descTex.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descTex.Format = DXGI_FORMAT_D32_FLOAT;
	descTex.Height = 720;
	descTex.Width = 1280;
	descTex.SampleDesc.Count = 4;

	ID3D11Texture2D* texture;

	HRESULT hr = this->mDevice->CreateTexture2D(&descTex, NULL, &texture);
	if (FAILED(hr))
	{
		MessageBox(0, L"Depth texture creation failed", L"error", MB_OK);
	}

	D3D11_DEPTH_STENCIL_DESC descSten;
	ZeroMemory(&descSten, sizeof(D3D11_DEPTH_STENCIL_DESC));
	descSten.DepthEnable = true;
	descSten.DepthFunc = D3D11_COMPARISON_LESS;
	descSten.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	descSten.StencilEnable = false;

	hr = this->mDevice->CreateDepthStencilState(&descSten, &this->mDSS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Depth stencil state creation failed", L"error", MB_OK);
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descStenV;
	ZeroMemory(&descStenV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descStenV.Format = DXGI_FORMAT_D32_FLOAT;
	descStenV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

	hr = this->mDevice->CreateDepthStencilView(texture, &descStenV, &this->mDSV);
	if (FAILED(hr))
	{
		MessageBox(0, L"Depth stencil view creation failed", L"error", MB_OK);
	}

	this->mContext->OMSetDepthStencilState(this->mDSS, 0);

	texture->Release();

}

void GraphicsHandler::setupView(int width, int height)
{
	this->mView.Height = height;
	this->mView.Width = width;
	this->mView.MaxDepth = 1.f;
	this->mView.MinDepth = 0.f;
	this->mView.TopLeftX = 0;
	this->mView.TopLeftY = 0;
}

void GraphicsHandler::setVP(ID3D11Buffer* vp)
{
	this->mContext->VSSetConstantBuffers(0, 1, &vp);
	this->mContext->GSSetConstantBuffers(0, 1, &vp);
}

void GraphicsHandler::setCamPos(ID3D11Buffer* pos)
{
	this->mContext->GSSetConstantBuffers(1, 1, &pos);
}

void GraphicsHandler::createParticleBuffers(int nrOfParticles)
{
	Particle* particles = new Particle[nrOfParticles];
	ZeroMemory(particles, sizeof(Particle) * nrOfParticles);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	float tempo;
	data.pSysMem = &tempo;

	this->mDeltaTimeBuffer.setupConstantBuffer(16, data, true, this->mDevice);

	data.pSysMem = particles;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.ByteWidth = nrOfParticles * sizeof(Particle);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = sizeof(Particle);

	ID3D11Buffer* structBuffer1 = nullptr;
	ID3D11Buffer* structBuffer2 = nullptr;

	this->mDevice->CreateBuffer(&desc, &data, &structBuffer1);
	this->mDevice->CreateBuffer(&desc, &data, &structBuffer2);

	delete[] particles;

	D3D11_BUFFER_UAV uav;

	uav.FirstElement = 0;
	uav.NumElements = nrOfParticles;
	uav.Flags = D3D11_BUFFER_UAV_FLAG_APPEND;

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));

	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer = uav;

	D3D11_BUFFER_SRV srv;
	ZeroMemory(&srv, sizeof(D3D11_BUFFER_SRV));
	srv.FirstElement = 0;
	srv.NumElements = nrOfParticles;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer = srv;

	this->mDevice->CreateUnorderedAccessView(structBuffer1, &uavDesc, &this->UAVS[0]);
	this->mDevice->CreateShaderResourceView(structBuffer1, &srvDesc, &this->SRVS[0]);

	//uav and srv for second buffer
	this->mDevice->CreateUnorderedAccessView(structBuffer2, &uavDesc, &this->UAVS[1]);
	this->mDevice->CreateShaderResourceView(structBuffer2, &srvDesc, &this->SRVS[1]);
	
	structBuffer1->Release();
	structBuffer2->Release();

	//this is for the indirect args buffer. For  constant buffer only first value is relevant rest is padding.
	//0: nr of verticies
	//1: nr of instances
	//2: start vertex
	//3: start instance
	//4: padding
	UINT* init = new UINT[5];
	init[0] = 0;
	init[1] = 0;
	init[2] = 0;
	init[3] = 0;
	init[4] = 0;

	//create constant buffer who holds the nr of particles
	D3D11_BUFFER_DESC nrBDesc;
	ZeroMemory(&nrBDesc, sizeof(D3D11_BUFFER_DESC));
	nrBDesc.ByteWidth = 4 * sizeof(UINT);
	nrBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	nrBDesc.Usage = D3D11_USAGE_DEFAULT;


	data.pSysMem = init;

	this->mDevice->CreateBuffer(&nrBDesc, &data, &this->particleCountBuffer);

	//create indirect argument buffer used for the drawIndirect call
	D3D11_BUFFER_DESC inDesc;
	ZeroMemory(&inDesc, sizeof(D3D11_BUFFER_DESC));
	inDesc.ByteWidth = 5 * sizeof(UINT);
	inDesc.Usage = D3D11_USAGE_DEFAULT;
	inDesc.MiscFlags = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;

	//sets nr of instances
	init[1] = 1;


	this->mDevice->CreateBuffer(&inDesc, &data, &this->IndirectArgsBuffer);

	delete[] init;
}

void GraphicsHandler::initParticles()
{
	this->mContext->CSSetUnorderedAccessViews(0, 1, &this->UAVS[0], 0);
	this->mContext->CSSetUnorderedAccessViews(1, 1, &this->UAVS[1], 0);
	this->mContext->CSSetConstantBuffers(1, 1, &this->particleCountBuffer);

	this->mShaderHandler.setCS(this->mParticleCS.injector, this->mContext);

	this->mContext->Dispatch(1, 1, 1);
	this->mContext->CopyStructureCount(this->particleCountBuffer, 0, this->UAVS[0]);

	this->mContext->CSSetUnorderedAccessViews(0, 1, &this->nullUAV, 0);
	this->mContext->CSSetUnorderedAccessViews(1, 1, &this->nullUAV, 0);
}

void GraphicsHandler::updateDeltaTimeBuffer(float dt)
{
	this->mDeltaTimeBuffer.updateBuffer(4, &dt, this->mContext);
}

void GraphicsHandler::injectParticles(ParticleEmitter* emitter)
{
	//TODO: UPPER CAP
	ID3D11Buffer* temp = emitter->getBuffer();
	UINT UAVFLAG = -1;

	this->mContext->CSSetConstantBuffers(0, 1, &temp);
	this->mContext->CSSetUnorderedAccessViews(0, 1, &this->UAVS[0], &UAVFLAG);
	this->mContext->CSSetConstantBuffers(1, 1, &this->particleCountBuffer);

	this->mShaderHandler.setCS(this->mParticleCS.injector, this->mContext);

	this->mContext->Dispatch(1, 1, 1);
	this->mContext->CopyStructureCount(this->particleCountBuffer, 0, this->UAVS[0]);

	this->mContext->CSSetUnorderedAccessViews(0, 1, &this->nullUAV, &UAVFLAG);
	this->mContext->CSSetUnorderedAccessViews(1, 1, &this->nullUAV, &UAVFLAG);
}

void GraphicsHandler::updateParticles()
{
	UINT UAVFLAG = -1;

	ID3D11Buffer* temp = this->mDeltaTimeBuffer.getBuffer();

	this->mContext->CSSetConstantBuffers(0, 1, &this->particleCountBuffer);
	this->mContext->CSSetConstantBuffers(1, 1, &temp);

	this->mContext->CSSetUnorderedAccessViews(0, 1, &this->UAVS[0], &UAVFLAG);
	this->mContext->CSSetUnorderedAccessViews(1, 1, &this->UAVS[1], 0);

	this->mShaderHandler.setCS(this->mParticleCS.updater, this->mContext);


	this->mContext->Dispatch(1, 1, 1);

	this->swapParticleBuffers();


	this->mContext->CopyStructureCount(this->particleCountBuffer, 0, this->UAVS[0]);
	this->mContext->CopyStructureCount(this->IndirectArgsBuffer, 0, this->UAVS[0]);

	this->mContext->CSSetUnorderedAccessViews(0, 1, &this->nullUAV, &UAVFLAG);
	this->mContext->CSSetUnorderedAccessViews(1, 1, &this->nullUAV, &UAVFLAG);
}

void GraphicsHandler::swapParticleBuffers()
{
	ID3D11UnorderedAccessView *tempUAV;
	ID3D11ShaderResourceView *tempSRV;
	tempUAV = this->UAVS[0];
	tempSRV = this->SRVS[0];

	this->UAVS[0] = this->UAVS[1];
	this->SRVS[0] = this->SRVS[1];

	this->UAVS[1] = tempUAV;
	this->SRVS[1] = tempSRV;

	tempSRV = nullptr;
	tempUAV = nullptr;

}

void GraphicsHandler::clear()
{
	float clearColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	this->mContext->ClearRenderTargetView(this->mBackBufferRTV, clearColor);
	this->mContext->ClearDepthStencilView(this->mDSV, D3D11_CLEAR_DEPTH, 1.f, 0);
}

void GraphicsHandler::render(Entity* entity)
{
	this->mShaderHandler.setShaders(this->mEntitySetup.vs, this->mEntitySetup.gs, this->mEntitySetup.ps, this->mContext);

	Mesh* mesh = dynamic_cast<Mesh*>(entity->getComponent(ComponentID::mesh));
	ID3D11Buffer* temp = mesh->getBuffer();

	UINT stride = sizeof(Vertex), offset = 0;

	if (entity->hasComponent(ComponentID::transformBuffer))
	{
		TransformBuffer* transform = dynamic_cast<TransformBuffer*>(entity->getComponent(ComponentID::transformBuffer));
		ID3D11Buffer* temp2 = transform->getBuffer();
		this->mContext->VSSetConstantBuffers(1, 1, &temp2);
		this->mShaderHandler.setVS(this->mEntitySetup.vsTransform, this->mContext);
	}

	if (entity->hasComponent(ComponentID::pointLight))
	{
		this->mShaderHandler.setPS(this->mEntitySetup.psLight, this->mContext);
	}

	this->mLightHandler.setConstantBuffer(this->mContext);

	this->mContext->RSSetViewports(1, &this->mView);
	this->mContext->OMSetRenderTargets(1, &this->mBackBufferRTV, this->mDSV);
	this->mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->mContext->IASetVertexBuffers(0, 1, &temp, &stride, &offset);
	this->mContext->Draw(mesh->getNrOfVertices(), 0);
}

void GraphicsHandler::renderParticles(Entity* entity)
{
	this->mShaderHandler.setShaders(this->mParticleSetup.vs, this->mParticleSetup.gs, this->mParticleSetup.ps, this->mContext);

	UINT stride = sizeof(Particle), offset = 0;

	ParticleEmitter* emitter = dynamic_cast<ParticleEmitter*>(entity->getComponent(ComponentID::particleEmitter));
	ID3D11Buffer* temp = emitter->getBuffer();

	this->mContext->RSSetViewports(1, &this->mView);
	this->mContext->OMSetRenderTargets(1, &this->mBackBufferRTV, this->mDSV);
	this->mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	this->mContext->IASetVertexBuffers(0, 1, &temp, &stride, &offset);
	this->mContext->Draw(emitter->getNrOfParticles(), 0);
}

void GraphicsHandler::renderParticlesGPU()
{
	this->mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	this->mContext->RSSetViewports(1, &this->mView);

	this->mShaderHandler.setShaders(this->mParticleSetup.vs, this->mParticleSetup.gs, this->mParticleSetup.ps, this->mContext);
	this->mContext->IASetInputLayout(nullptr);
	this->mContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);

	this->mContext->VSSetShaderResources(0, 1, &this->SRVS[0]);


	this->mContext->OMSetRenderTargets(1, &this->mBackBufferRTV, this->mDSV);

	this->mContext->DrawInstancedIndirect(this->IndirectArgsBuffer, 0);
}

void GraphicsHandler::present()
{
	this->mSwapChain->Present(0, 0);
}

ID3D11Device* GraphicsHandler::getDevice()
{
	return this->mDevice;
}

ID3D11DeviceContext* GraphicsHandler::getDeviceContext()
{
	return this->mContext;
}

LightHandler* GraphicsHandler::getLightHandler()
{
	return &this->mLightHandler;
}
