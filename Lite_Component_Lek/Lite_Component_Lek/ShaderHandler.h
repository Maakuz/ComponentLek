#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include "D3DHeader.h"
#include <vector>

class ShaderHandler
{
private:
	std::vector<ID3D11VertexShader*> mVertexShaders;
	std::vector<ID3D11GeometryShader*> mGeometryShaders;
	std::vector<ID3D11PixelShader*> mPixelShaders;
	std::vector<ID3D11InputLayout*> mInputLayout;

public:
	ShaderHandler();
	virtual ~ShaderHandler();

	int setupVertexShader(ID3D11Device* device, wchar_t* name, char* entrypoint, D3D11_INPUT_ELEMENT_DESC* desc, UINT nrOfElements);
	int setupGeometryShader();
	int setupPixelShader(ID3D11Device* device, wchar_t* name, char* entrypoint);

	void setShaders(int vs, int gs, int ps, ID3D11DeviceContext* context);
};

#endif