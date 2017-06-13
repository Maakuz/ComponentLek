#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H
#include "DirectionalLight.h"
#include <vector>

class LightHandler
{
private:
	std::vector<DirectionalLight*> mDirLights;
	bool mLightingChanged;
	ID3D11Buffer* mDirLightBuffer;

public:
	LightHandler();
	virtual ~LightHandler();

	void setupLightBuffers(ID3D11Device* device);

	void addDirectionalLight(DirectionalLight* light);
	void removeDirectionalLight(DirectionalLight* light);
	void setConstantBuffer(ID3D11DeviceContext* context);
};
#endif
