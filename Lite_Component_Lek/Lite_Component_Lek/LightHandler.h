#ifndef LIGHTHANDLER_H
#define LIGHTHANDLER_H
#include "DirectionalLight.h"
#include "PointLight.h"
#include <vector>

//This class is weird but works. Don't argue
class LightHandler
{
private:
	std::vector<DirectionalLight*> mDirLights;
	std::vector<PointLight*> mPointLights;
	bool mDirLightChanged;
	bool mPointLightChanged;
	ID3D11Buffer* mDirLightBuffer;
	ID3D11Buffer* mPointLightBuffer;

public:
	LightHandler();
	virtual ~LightHandler();

	void setupLightBuffers(ID3D11Device* device);

	void addDirectionalLight(DirectionalLight* light);
	void addPointLight(PointLight* light);
	void removeDirectionalLight(DirectionalLight* light);
	void setConstantBuffer(ID3D11DeviceContext* context);
};
#endif
