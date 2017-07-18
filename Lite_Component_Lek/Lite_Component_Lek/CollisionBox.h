#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

#include "Component.h"
#include "D3DHeader.h"
#include "SimpleMath.h"
#include <sstream>

class CollisionBox : public Component
{
private:
	DirectX::SimpleMath::Vector3 mLength;
	DirectX::SimpleMath::Vector3 mPos;

public:
	CollisionBox(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 length);
	~CollisionBox();

	bool intersects(const CollisionBox& otherBox);

	void setPosition(DirectX::SimpleMath::Vector3 position);

	std::string printPos() const;
	std::string toString() const;
};

#endif