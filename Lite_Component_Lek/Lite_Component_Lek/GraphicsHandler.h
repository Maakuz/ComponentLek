#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H

#include "SDL.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

class GraphicsHandler 
{
private:
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;
	ID3D11RenderTargetView* mBackBufferRTV;
	ID3D11Debug* mDebugDevice;

public:
	GraphicsHandler();
	virtual ~GraphicsHandler();

	HRESULT setup3DContent();

	void clear();
	void render();
	void present();

};

#endif
