#ifndef MESH_H
#define MESH_H
#include "Component.h"
#include "D3DHeader.h"
#include <vector>

struct Vertex
{
	float x, y, z;
	float r, g, b;
};

class Mesh : public Component
{
private:
	ID3D11Buffer* mVertexBuffer;

public:
	Mesh();
	~Mesh();

	bool loadMesh(std::vector<Vertex> vertices, ID3D11Device* device);

	ID3D11Buffer* getBuffer();
};
#endif