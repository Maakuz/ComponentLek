#ifndef VELOCITY_H
#define VELOCITY_H
#include "Component.h"
#include "D3DHeader.h"
#include "SimpleMath.h"
class Velocity : public Component
{
private:
	DirectX::SimpleMath::Vector3 mVelocity;
	float mFriction;

public:
	Velocity(float friction = 0);
	virtual ~Velocity();

	void setVelocity(DirectX::SimpleMath::Vector3 velocity);
	void addVelocity(DirectX::SimpleMath::Vector3 velocity);
	void addXVelocity(float velocity);
	void addYVelocity(float velocity);
	void addZVelocity(float velocity);

	void applyFriction();

	DirectX::SimpleMath::Vector3 getVelocity() const;

	void setFriction(float friction);
};

#endif
