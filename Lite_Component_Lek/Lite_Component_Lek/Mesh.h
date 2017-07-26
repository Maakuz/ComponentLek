#ifndef MESH_H
#define MESH_H
#include "Component.h"
#include "EasyBuffer.h"
#include <vector>

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
	float r, g, b;
};

class Mesh : public Component
{
private:
	EasyBuffer mVertexBuffer;
	int mNrOfVertices;

public:
	Mesh();
	virtual ~Mesh();

	bool loadMesh(std::vector<Vertex> vertices, ID3D11Device* device);

	ID3D11Buffer* getBuffer();
	int getNrOfVertices() const;
};
#endif