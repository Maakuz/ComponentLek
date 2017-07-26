#include "Camera.h"
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height) : Component(ComponentID::camera)
{
	float angle = 0.5f * M_PI;

	this->mPos = Vector3(-10, 10, 0);
	this->mForward = Vector3(0.5f, -0.5f, 0);
	this->mRight = Vector3(0, 0, 1);
	this->mUp = Vector3(0.5f, 0.5f, 0);
	
	this->mYaw = 0;
	this->mPitch = 0;

	this->mVP.projection = DirectX::XMMatrixPerspectiveFovLH(angle, (float)width/(float)height, 0.1f, 100.f);
	this->mVP.projection = this->mVP.projection.Transpose();

	this->mVP.view = DirectX::XMMatrixLookToLH(this->mPos, this->mForward, this->mUp);
	this->mVP.view = this->mVP.view.Transpose();

}

Camera::~Camera()
{
	
}

void Camera::updateCamera(ID3D11DeviceContext* context)
{
	Matrix view = DirectX::XMMatrixLookToLH(this->mPos, this->mForward, this->mUp);
	view = view.Transpose();

	if (this->mVP.view != view)
	{
		this->mVP.view = view;
		Matrix VP = this->mVP.projection * this->mVP.view;

		this->mVPBuffer.updateBuffer(sizeof(VP), &VP, context);
		this->mPosBuffer.updateBuffer(sizeof(float) * 3, &this->mPos, context);
	}
}

ID3D11Buffer* Camera::getBuffer()
{
	return this->mVPBuffer.getBuffer();
}

ID3D11Buffer* Camera::getPosBuffer()
{
	return this->mPosBuffer.getBuffer();
}

HRESULT Camera::setupBuffer(ID3D11Device* device)
{
	//Backwards because right to left
	Matrix VP =  this->mVP.projection * this->mVP.view;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &VP;

	HRESULT hr = this->mVPBuffer.setupConstantBuffer(sizeof(Matrix), data, true, device);

	data.pSysMem = &this->mPos;

	if (SUCCEEDED(hr))
		hr = this->mPosBuffer.setupConstantBuffer(sizeof(float) * 4, data, true, device);

	return hr;
}

void Camera::setForward(DirectX::SimpleMath::Vector3 forward)
{
	this->mForward = forward;
}

void Camera::setUp(DirectX::SimpleMath::Vector3 up)
{
	this->mUp = up;
}

void Camera::setRight(DirectX::SimpleMath::Vector3 right)
{
	this->mRight = right;
}

void Camera::setPos(DirectX::SimpleMath::Vector3 pos)
{
	this->mPos = pos;
}

DirectX::SimpleMath::Vector3 Camera::getForward() const
{
	return this->mForward;
}

DirectX::SimpleMath::Vector3 Camera::getUp() const
{
	return this->mUp;
}

DirectX::SimpleMath::Vector3 Camera::getRight() const
{
	return this->mRight;
}

DirectX::SimpleMath::Vector3 Camera::getPos() const
{
	return this->mPos;
}
