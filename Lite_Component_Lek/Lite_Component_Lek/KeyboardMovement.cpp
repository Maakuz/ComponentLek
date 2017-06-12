#include "KeyboardMovement.h"

KeyboardMovement::KeyboardMovement(float maxSpeed) : Component(ComponentID::keyboardInput)
{
	this->mSpeed = { 0 };
	this->mMaxSpeed = maxSpeed;
}

KeyboardMovement::~KeyboardMovement()
{
}

void KeyboardMovement::handleKeyPress(SDL_KeyboardEvent const& key)
{
	switch (key.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		this->mSpeed.z = mMaxSpeed;
		break;

	case SDL_SCANCODE_D:
		this->mSpeed.z = -mMaxSpeed;
		break;

	case SDL_SCANCODE_W:
		this->mSpeed.x = mMaxSpeed;
		break;

	case SDL_SCANCODE_S:
		this->mSpeed.x = -mMaxSpeed;
		break;
	}
}

void KeyboardMovement::handleKeyRelease(SDL_KeyboardEvent const& key)
{
	switch (key.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		this->mSpeed.z = 0;
		break;

	case SDL_SCANCODE_W:
		this->mSpeed.x = 0;
		break;

	case SDL_SCANCODE_S:
		this->mSpeed.x = 0;
		break;

	case SDL_SCANCODE_D:
		this->mSpeed.z = 0;
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
