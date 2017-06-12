#include "Velocity.h"

Velocity::Velocity(float friction) : Component(ComponentID::velocity)
{
	this->mVelocity = { 0 };
	this->mFriction = friction;
}

Velocity::~Velocity()
{
}

void Velocity::setVelocity(DirectX::SimpleMath::Vector3 velocity)
{
	this->mVelocity = velocity;
}

void Velocity::addVelocity(DirectX::SimpleMath::Vector3 velocity)
{
	this->mVelocity += velocity;
}

void Velocity::applyFriction()
{
	this->mVelocity *= this->mFriction;
}

DirectX::SimpleMath::Vector3 Velocity::getVelocity() const
{
	return this->mVelocity;
}

void Velocity::setFriction(float friction)
{
	this->mFriction = friction;
}
