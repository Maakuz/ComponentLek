#include "Particle.h"

Particle::Particle(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity, DirectX::SimpleMath::Vector3 color)
{
	this->mPos = pos;
	this->mVelocity = velocity;
	this->mColor = color;
}

Particle::~Particle()
{
}

void Particle::decreaseLifeTime(float deltaTime)
{
	this->mLifeTime -= deltaTime;
}

DirectX::SimpleMath::Vector3 Particle::getPos() const
{
	return this->mPos;
}

DirectX::SimpleMath::Vector3 Particle::getVelocity() const
{
	return this->mVelocity;
}

DirectX::SimpleMath::Vector3 Particle::getColor() const
{
	return this->mColor;
}

float Particle::getLifeTime() const
{
	return this->mLifeTime;
}

void Particle::setPos(DirectX::SimpleMath::Vector3 pos)
{
	this->mPos = pos;
}

void Particle::setVelocity(DirectX::SimpleMath::Vector3 velocity)
{
	this->mVelocity = velocity;
}

void Particle::setColor(DirectX::SimpleMath::Vector3 color)
{
	this->mColor = color;
}

void Particle::setLifeTime(float life)
{
	this->mLifeTime = life;
}
