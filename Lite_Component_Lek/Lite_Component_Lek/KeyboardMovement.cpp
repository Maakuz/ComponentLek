#include "KeyboardMovement.h"

KeyboardMovement::KeyboardMovement(float maxSpeed, Velocity* vel) : Component(ComponentID::keyboardInput)
{
	this->mMaxSpeed = maxSpeed;

	if (vel)
		this->mVels.push_back(vel);

}

KeyboardMovement::~KeyboardMovement()
{
}

void KeyboardMovement::update(float dt)
{
	for (size_t i = 0; i < this->mVels.size(); i++)
	{
		this->mVels[i]->addVelocity(this->mSpeed);
	}
}

void KeyboardMovement::handleKeyPress(SDL_KeyboardEvent const& key)
{
	switch (key.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		this->mSpeed.z = this->mMaxSpeed;
		break;

	case SDL_SCANCODE_D:
		this->mSpeed.z = -this->mMaxSpeed;
		break;

	case SDL_SCANCODE_W:
		this->mSpeed.x = this->mMaxSpeed;
		break;

	case SDL_SCANCODE_S:
		this->mSpeed.x = -this->mMaxSpeed;
		break;

	//jumping
	case SDL_SCANCODE_SPACE:
		for (size_t i = 0; i < this->mVels.size(); i++)
		{
			this->mVels[i]->addYVelocity(0.1);
		}
		break;
	}
}

void KeyboardMovement::handleKeyRelease(SDL_KeyboardEvent const& key)
{
	switch (key.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		if (this->mSpeed.z == this->mMaxSpeed)
			this->mSpeed.z = 0;
		break;			 
						 
	case SDL_SCANCODE_D:
		if (this->mSpeed.z == -this->mMaxSpeed)
			this->mSpeed.z = 0;
		break;			 
						 
	case SDL_SCANCODE_W: 
		if (this->mSpeed.x == this->mMaxSpeed)
			this->mSpeed.x = 0;
		break;			 
						 
	case SDL_SCANCODE_S: 
		if (this->mSpeed.x == -this->mMaxSpeed)
			this->mSpeed.x = 0;
		break;
	}
}

DirectX::SimpleMath::Vector3 KeyboardMovement::getSpeed() const
{
	return this->mSpeed;
}

void KeyboardMovement::setSpeed(DirectX::SimpleMath::Vector3 speed)
{
	this->mSpeed = speed;
}

void KeyboardMovement::addVelocity(Velocity* vel)
{
	this->mVels.push_back(vel);
}
