#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "Component.h"
#include "D3DHeader.h"
#include "SimpleMath.h"



class DirectionalLight : public Component
{
private:
	struct DirColor
	{
		DirectX::SimpleMath::Vector4 dir;
		DirectX::SimpleMath::Vector4 color;
	};

	DirColor mDirColor;

public:
	DirectionalLight(DirectX::SimpleMath::Vector3 dir = DirectX::SimpleMath::Vector3(0, 0, 0), DirectX::SimpleMath::Vector3 color = DirectX::SimpleMath::Vector3(1, 1, 1));
	virtual ~DirectionalLight();

	DirectX::SimpleMath::Vector4 getDir() const;
	void setDir(DirectX::SimpleMath::Vector3);
	DirectX::SimpleMath::Vector4 getColor() const;
	void setColor(DirectX::SimpleMath::Vector3);

};
#endif
