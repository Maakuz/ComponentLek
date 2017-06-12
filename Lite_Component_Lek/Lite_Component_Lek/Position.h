#ifndef POSITION_H
#define POSITION_H
#include "Component.h"
#include "D3DHeader.h"
#include "SimpleMath.h"

class Position : public Component
{
private:
	DirectX::SimpleMath::Vector3 mPos;

public:
	Position();
	virtual ~Position();

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	void move(DirectX::SimpleMath::Vector3 offset);
	DirectX::SimpleMath::Vector3 getPosition() const;
	DirectX::SimpleMath::Matrix getTransformMatrix() const;

};
#endif