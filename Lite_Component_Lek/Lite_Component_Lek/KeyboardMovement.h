#ifndef KEYBOARDMOVEMENT_H
#define KEYBOARDMOVEMENT_H

#include "SDL.h"
#include "Velocity.h"
#include <vector>

class KeyboardMovement : public Component
{
private:
	std::vector<Velocity*> mVels;
	float mMaxSpeed;
	DirectX::SimpleMath::Vector3 mSpeed;

public:
	KeyboardMovement(float maxSpeed = 1, Velocity* vel = nullptr);
	virtual ~KeyboardMovement();

	void handleKeyPress(SDL_KeyboardEvent const &key);
	void handleKeyRelease(SDL_KeyboardEvent const &key);

	void update(float dt);

	DirectX::SimpleMath::Vector3 getSpeed() const;
	void setSpeed(DirectX::SimpleMath::Vector3 speed);

	void addVelocity(Velocity* vel);
};

#endif