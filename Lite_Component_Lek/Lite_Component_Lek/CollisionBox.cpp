#include "CollisionBox.h"

CollisionBox::CollisionBox(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 length) : Component(ComponentID::collisionBox)
{
	this->mLength = length;
	this->mPos = pos;
}

CollisionBox::~CollisionBox()
{
}

bool CollisionBox::intersects(const CollisionBox & otherBox)
{
	DirectX::SimpleMath::Vector3 max = this->mPos + this->mLength;
	DirectX::SimpleMath::Vector3 otherMax = otherBox.mPos + otherBox.mLength;

	if (this->mPos.x >= otherMax.x)
		return false;

	if (this->mPos.y >= otherMax.y)
		return false;

	if (this->mPos.z >= otherMax.z)
		return false;

	if (otherBox.mPos.x >= max.x)
		return false;

	if (otherBox.mPos.y >= max.y)
		return false;

	if (otherBox.mPos.z >= max.z)
		return false;

	return true;
}

void CollisionBox::setPosition(DirectX::SimpleMath::Vector3 position)
{
	this->mPos = position;
}

std::string CollisionBox::printPos() const
{
	std::stringstream ret;
	ret << "x: " << this->mPos.x << " y: " << this->mPos.y << " z: " << this->mPos.z;
	return ret.str();
}

std::string CollisionBox::toString() const
{
	std::stringstream ret;
	ret << this->printPos() << std::endl << "xLength: " << this->mLength.x << " yLength: " << this->mLength.y << " zLength: " << this->mLength.z;
	
	return ret.str();
}
