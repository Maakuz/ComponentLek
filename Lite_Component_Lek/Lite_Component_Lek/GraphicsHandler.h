#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H

#include "SDL.h"
#include "Entity.h"
#include "ShaderHandler.h"

class GraphicsHandler 
{
private:
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;
	ID3D11RenderTargetView* mBackBufferRTV;
	ID3D11Debug* mDebugDevice;
	D3D11_VIEWPORT mView;

	ShaderHandler mShaderHandler;

	struct shaderSetup { int vs; int gs; int ps; };
	shaderSetup mEntitySetup;

public:
	GraphicsHandler();
	virtual ~GraphicsHandler();

	HRESULT setup3DContent();
	void setupShaders();
	void setupView(int width, int height);

	void clear();
	void render(Entity* entity);
	void present();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
};

#endif
