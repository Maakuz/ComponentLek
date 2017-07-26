#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Component.h"
#include "EasyBuffer.h"
#include "SimpleMath.h"
#include <vector>

#define MAX_PARTICLES_PER_EMITTER 10000

struct Particle
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 velocity;
	DirectX::SimpleMath::Vector3 color;
	float lifeTime;
};



class ParticleEmitter : public Component
{
private:
	std::vector<Particle> mParticles;
	DirectX::SimpleMath::Vector3 mPos;

	EasyBuffer mEmitterBuffer;

public:
	ParticleEmitter(DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(0, 0, 0));
	~ParticleEmitter();

	void setupBuffer(ID3D11Device* device);

	void update(float dt, ID3D11DeviceContext* context);

	void addParticle(Particle particle);
	int getNrOfParticles() const;
	ID3D11Buffer* getBuffer();

	void setPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 getPos() const;

	void createShape(ID3D11DeviceContext* context);
};
#endif