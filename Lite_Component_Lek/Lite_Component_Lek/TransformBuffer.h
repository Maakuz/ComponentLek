#ifndef TRANSFORMBUFFER_H
#define TRANSFORMBUFFER_H
#include "Component.h"
#include "EasyBuffer.h"
#include "SimpleMath.h"

class TransformBuffer : public Component
{
private:
	EasyBuffer mBuffer;
	DirectX::SimpleMath::Matrix mTransform;

public:
	TransformBuffer();
	virtual ~TransformBuffer();

	void setupBuffer(ID3D11Device* device);
	void updateBuffer(ID3D11DeviceContext* context);
	void resetMatrix();
	void multiplyCurrent(DirectX::SimpleMath::Matrix toMultiply);
	ID3D11Buffer* getBuffer();
};
#endif