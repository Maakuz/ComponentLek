#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() : Component(ComponentID::particleEmitter)
{
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::setupBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	this->mBuffer.setupVertexBuffer(MAX_PARTICLES_PER_EMITTER * sizeof(Particle), data, true, device);
}

void ParticleEmitter::update(float dt)
{
}

void ParticleEmitter::addParticle(Particle particle)
{
}

void ParticleEmitter::createShape(ID3D11DeviceContext* context)
{
	this->mParticles.push_back(Particle(DirectX::SimpleMath::Vector3(-5, 0, 0), DirectX::SimpleMath::Vector3(0, 0.03f, 0)));

	this->mBuffer.updateBuffer(this->mParticles.size(), &this->mParticles[0], context);
}
