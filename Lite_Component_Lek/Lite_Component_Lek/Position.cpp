#include "Position.h"

Position::Position(float x, float y, float z) : Component(ComponentID::position)
{
	this->mPos = DirectX::SimpleMath::Vector3(x, y, z);
}

Position::~Position()
{
}

void Position::setPosition(DirectX::SimpleMath::Vector3 pos)
{
	this->mPos = pos;
}

void Position::move(DirectX::SimpleMath::Vector3 offset)
{
	this->mPos += offset;
}

DirectX::SimpleMath::Vector3 Position::getPosition() const
{
	return this->mPos;
}

DirectX::SimpleMath::Matrix Position::getTransformMatrix() const
{
	return DirectX::SimpleMath::Matrix::CreateTranslation(this->mPos).Transpose();
}

std::string Position::toString()
{
	std::stringstream ret;
	ret << "x: " << this->mPos.x << " y: " << this->mPos.y << " z: " << this->mPos.z;

	return ret.str();
}
