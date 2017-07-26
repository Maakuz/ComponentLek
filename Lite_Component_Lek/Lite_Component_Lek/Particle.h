#ifndef PARTICLE_H
#define PARTICLE_H
#include "D3DHeader.h"
#include "SimpleMath.h"

class Particle
{
private:
	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mVelocity;
	DirectX::SimpleMath::Vector3 mColor;
	float mLifeTime;

public:
	Particle(DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(0, 0, 0), DirectX::SimpleMath::Vector3 velocity = DirectX::SimpleMath::Vector3(0, 0, 0), DirectX::SimpleMath::Vector3 color = DirectX::SimpleMath::Vector3(0, 0, 0));
	~Particle();

	void decreaseLifeTime(float deltaTime);

	DirectX::SimpleMath::Vector3 getPos() const;
	DirectX::SimpleMath::Vector3 getVelocity() const;
	DirectX::SimpleMath::Vector3 getColor() const;
	float getLifeTime() const;

	void setPos(DirectX::SimpleMath::Vector3 pos);
	void setVelocity(DirectX::SimpleMath::Vector3 velocity);
	void setColor(DirectX::SimpleMath::Vector3 color);
	void setLifeTime(float life);
};

#endif