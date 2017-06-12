#ifndef KEYBOARDMOVEMENT_H
#define KEYBOARDMOVEMENT_H

#include "SDL.h"
#include "Velocity.h"

class KeyboardMovement : public Component
{
private:
	DirectX::SimpleMath::Vector3 mSpeed;
	float mMaxSpeed;

public:
	KeyboardMovement(float maxSpeed = 1);
	virtual ~KeyboardMovement();

	void handleKeyPress(SDL_KeyboardEvent const &key);
	void handleKeyRelease(SDL_KeyboardEvent const &key);

	DirectX::SimpleMath::Vector3 getSpeed() const;
	void setSpeed(DirectX::SimpleMath::Vector3 speed);
};

#endif