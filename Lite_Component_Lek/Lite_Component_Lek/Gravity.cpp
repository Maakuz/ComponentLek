#include "Gravity.h"

Gravity::Gravity(float accel) :  Component(ComponentID::gravity)
{
	this->mGravForce = accel;
}

Gravity::~Gravity()
{
}

void Gravity::setGravForce(float force)
{
	this->mGravForce = force;
}

float Gravity::getGravForce() const
{
	return this->mGravForce;
}


