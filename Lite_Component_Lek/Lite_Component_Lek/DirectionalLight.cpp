#include "DirectionalLight.h"
using namespace DirectX::SimpleMath;

DirectionalLight::DirectionalLight(Vector3 dir, Vector3 color) : Component(ComponentID::directionalLight)
{
	this->mDirColor.dir = Vector4(dir.x, dir.y, dir.z, 0);
	this->mDirColor.color =  Vector4(color.x, color.y, color.z, 0);
}

DirectionalLight::~DirectionalLight()
{
}

DirectX::SimpleMath::Vector4 DirectionalLight::getDir() const
{
	return this->mDirColor.dir;
}

void DirectionalLight::setDir(DirectX::SimpleMath::Vector3 dir)
{
	this->mDirColor.dir = Vector4(dir.x, dir.y, dir.z, 0);
}

DirectX::SimpleMath::Vector4 DirectionalLight::getColor() const
{
	return this->mDirColor.color;
}

void DirectionalLight::setColor(DirectX::SimpleMath::Vector3 color)
{
	this->mDirColor.color = Vector4(color.x, color.y, color.z, 0);
}