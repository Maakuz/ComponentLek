#ifndef CAMERA_H
#define CAMERA_H
#include "Component.h"
#include "SimpleMath.h"
#include "D3DHeader.h"

#define _USE_MATH_DEFINES
#include <math.h>

struct VP
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
	VP mVP;

	ID3D11Buffer* mVPBuffer;

public:
	Camera(int width, int height);
	~Camera();


};

#endif