#include "PointLight.h"

PointLight::PointLight(float radius, DirectX::SimpleMath::Vector3 pos) : Component(ComponentID::pointLight)
{
	this->mRadius = radius;
	this->mPos = pos;
}

PointLight::~PointLight()
{
}

DirectX::SimpleMath::Vector3 PointLight::getPos() const
{
	return this->mPos;
}

void PointLight::setPos(DirectX::SimpleMath::Vector3 pos)
{
	this->mPos = pos;
}

float PointLight::getRadius() const
{
	return this->mRadius;
}

void PointLight::setRadius(float radius)
{
	this->mRadius = radius;
}
