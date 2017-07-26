#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H

#include "SDL.h"
#include "Entity.h"
#include "ShaderHandler.h"
#include "TransformBuffer.h"
#include "LightHandler.h"

class GraphicsHandler 
{
private:
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;
	ID3D11RenderTargetView* mBackBufferRTV;
	ID3D11DepthStencilState* mDSS;
	ID3D11DepthStencilView* mDSV;
	ID3D11Debug* mDebugDevice;
	D3D11_VIEWPORT mView;
	LightHandler mLightHandler;

	ShaderHandler mShaderHandler;

	struct ShaderSetup { int vs; int vsTransform; int gs; int ps; int psLight; };
	ShaderSetup mEntitySetup;
	ShaderSetup mParticleSetup;

public:
	GraphicsHandler();
	virtual ~GraphicsHandler();

	HRESULT setup3DContent();
	void setupShaders();
	void setupLightHandler();
	void setupDepthStencil();
	void setupView(int width, int height);
	void setVP(ID3D11Buffer* vp);

	void clear();
	void render(Entity* entity);
	void renderParticles(Entity* entity);
	void present();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	LightHandler* getLightHandler();
};

#endif
