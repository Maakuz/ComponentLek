#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Component.h"
#include "D3DHeader.h"
#include "SimpleMath.h"

class PointLight : public Component
{
private:
	DirectX::SimpleMath::Vector3 mPos;
	float mRadius;

public:
	PointLight(float radius = 0, DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(0, 0, 0));
	~PointLight();

	DirectX::SimpleMath::Vector3 getPos() const;
	void setPos(DirectX::SimpleMath::Vector3 pos);

	float getRadius() const;
	void setRadius(float radius);
};
#endif