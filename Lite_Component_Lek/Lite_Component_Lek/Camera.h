#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"
#include "EasyBuffer.h"
#include "SimpleMath.h"

#define _USE_MATH_DEFINES
#include <math.h>

struct VPStruct
{
	DirectX::SimpleMath::Matrix view;
	DirectX::SimpleMath::Matrix projection;
};

class Camera : public Component
{
private:
	DirectX::SimpleMath::Vector3 mPos;
	DirectX::SimpleMath::Vector3 mForward;
	DirectX::SimpleMath::Vector3 mUp;
	DirectX::SimpleMath::Vector3 mRight;

	float mPitch;
	float mYaw;
	VPStruct mVP;

	EasyBuffer mVPBuffer;

public:
	Camera(int width = 0, int height = 0);
	~Camera();

	void updateCamera(ID3D11DeviceContext* context);
	ID3D11Buffer* getBuffer();

	HRESULT setupBuffer(ID3D11Device* device);

	void setForward(DirectX::SimpleMath::Vector3 forward);
	void setUp(DirectX::SimpleMath::Vector3 up);
	void setRight(DirectX::SimpleMath::Vector3 right);
	void setPos(DirectX::SimpleMath::Vector3 pos);

	DirectX::SimpleMath::Vector3 getForward() const;
	DirectX::SimpleMath::Vector3 getUp() const;
	DirectX::SimpleMath::Vector3 getRight() const;
	DirectX::SimpleMath::Vector3 getPos() const;
};

#endif