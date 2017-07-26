#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Component.h"
#include "Particle.h"
#include "EasyBuffer.h"
#include <vector>

#define MAX_PARTICLES_PER_EMITTER 256

class ParticleEmitter : public Component
{
private:
	std::vector<Particle> mParticles;
	EasyBuffer mBuffer;
	DirectX::SimpleMath::Vector3 mPos;

public:
	ParticleEmitter(DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(0, 0, 0));
	~ParticleEmitter();

	void setupBuffer(ID3D11Device* device);

	void update(float dt);

	void addParticle(Particle particle);
	int getNrOfParticles() const;
	ID3D11Buffer* getBuffer();

	void createShape(ID3D11DeviceContext* context);
};
#endif