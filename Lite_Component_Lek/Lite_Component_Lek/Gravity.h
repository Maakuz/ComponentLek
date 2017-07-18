#ifndef GRAVITY_H
#define GRAVITY_H

#include "Component.h"

class Gravity : public Component
{
private:
	float mGravForce;

public:
	Gravity(float accel = 1.0f);
	~Gravity();

	void setGravForce(float force);
	float getGravForce() const;
};
#endif