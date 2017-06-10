#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H

#include "SDL.h"
#include "D3DHeader.h"
#include "Entity.h"

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
	void render(Entity* entity);
	void present();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
};

#endif
