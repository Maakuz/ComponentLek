#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(DirectX::SimpleMath::Vector3 pos) : Component(ComponentID::particleEmitter)
{
	this->mPos = pos;
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

int ParticleEmitter::getNrOfParticles() const
{
	return this->mParticles.size();
}

ID3D11Buffer* ParticleEmitter::getBuffer()
{
	return this->mBuffer.getBuffer();
}

void ParticleEmitter::createShape(ID3D11DeviceContext* context)
{
	this->mParticles.push_back(Particle(this->mPos + DirectX::SimpleMath::Vector3(-5, 0, 0), DirectX::SimpleMath::Vector3(0, 0.03f, 0)));

	this->mBuffer.updateBuffer(this->mParticles.size(), &this->mParticles[0], context);
}
