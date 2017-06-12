#include "Camera.h"
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height) : Component(ComponentID::camera)
{
	float angle = 0.5f * M_PI;

	this->mVPBuffer = nullptr;

	this->mPos = Vector3(-10, 0, 0);
	this->mForward = Vector3(1, 0, 0);
	this->mRight = Vector3(0, 0, 1);
	this->mUp = Vector3(0, 1, 0);
	
	this->mYaw = 0;
	this->mPitch = 0;

	this->mVP.projection = DirectX::XMMatrixPerspectiveFovLH(angle, (float)width/(float)height, 0.1f, 100.f);
	this->mVP.projection = this->mVP.projection.Transpose();

	this->mVP.view = DirectX::XMMatrixLookToLH(this->mPos, this->mForward, this->mUp);
	this->mVP.view = this->mVP.view.Transpose();
}

Camera::~Camera()
{
	this->mVPBuffer->Release();
}

void Camera::updateCamera(ID3D11DeviceContext* context)
{
	Matrix view = DirectX::XMMatrixLookToLH(this->mPos, this->mForward, this->mUp);
	view = view.Transpose();

	if (this->mVP.view != view)
	{
		this->mVP.view = view;
		Matrix VP = this->mVP.projection * this->mVP.view;

		D3D11_MAPPED_SUBRESOURCE data;

		context->Map(this->mVPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

		memcpy(data.pData, &VP, sizeof(VP));

		context->Unmap(this->mVPBuffer, 0);
	}


}

ID3D11Buffer* Camera::getBuffer()
{
	return this->mVPBuffer;
}

HRESULT Camera::setupBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(Matrix);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;

	//Backwards because right to left
	Matrix VP =  this->mVP.projection * this->mVP.view;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = &VP;

	HRESULT hr = device->CreateBuffer(&desc, &data, &this->mVPBuffer);

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
