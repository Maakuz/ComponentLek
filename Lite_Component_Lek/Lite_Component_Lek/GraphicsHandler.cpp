#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler()
{
	this->mBackBufferRTV = nullptr;
	this->mContext = nullptr;
	this->mDebugDevice = nullptr;
	this->mDevice = nullptr;
	this->mSwapChain = nullptr;
}

GraphicsHandler::~GraphicsHandler()
{
	this->mBackBufferRTV->Release();
	this->mContext->Release();
	this->mDevice->Release();
	this->mSwapChain->Release();




	//this->mDebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	this->mDebugDevice->Release();
}

HRESULT GraphicsHandler::setup3DContent() {
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

void GraphicsHandler::clear()
{
	float clearColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	this->mContext->ClearRenderTargetView(this->mBackBufferRTV, clearColor);
}

void GraphicsHandler::render()
{
}

void GraphicsHandler::present()
{
	this->mSwapChain->Present(0, 0);
}
