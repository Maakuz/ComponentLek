#ifndef EASYBUFFER_H
#define EASYBUFFER_H
#include "D3DHeader.h"

class EasyBuffer
{
private:
	ID3D11Buffer* mBuffer;
	bool mIsDynamic;

public:
	EasyBuffer();
	~EasyBuffer();

	bool setupConstantBuffer(UINT size, D3D11_SUBRESOURCE_DATA& data, bool isDynamic, ID3D11Device* device);
	bool setupVertexBuffer(UINT size, D3D11_SUBRESOURCE_DATA& data, bool isDynamic, ID3D11Device* device);

	void updateBuffer(UINT size, void* toCopy, ID3D11DeviceContext* context);

	ID3D11Buffer* getBuffer();
};

#endif