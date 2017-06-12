#include "Position.h"

Position::Position() : Component(ComponentID::position)
{
	this->mPos = { 0 };
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
