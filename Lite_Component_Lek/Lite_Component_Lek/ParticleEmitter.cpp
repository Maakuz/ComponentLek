#include "ParticleEmitter.h"
using namespace DirectX::SimpleMath;

ParticleEmitter::ParticleEmitter(Vector3 pos) : Component(ComponentID::particleEmitter)
{
	this->mPos = pos;
	this->mParticles.reserve(MAX_PARTICLES_PER_EMITTER);
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::setupBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	//data.pSysMem = mParticles.data();
	//this->mParticleBuffer.setupVertexBuffer(MAX_PARTICLES_PER_EMITTER * sizeof(Particle), data, true, device);
	
	data.pSysMem = &this->mPos;
	this->mEmitterBuffer.setupConstantBuffer(16, data, true, device);
}

void ParticleEmitter::update(float dt, ID3D11DeviceContext* context)
{
	this->mEmitterBuffer.updateBuffer(sizeof(mPos), &this->mPos, context);
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
	return this->mEmitterBuffer.getBuffer();
}

void ParticleEmitter::setPosition(Vector3 pos)
{
	this->mPos = pos;
}

Vector3 ParticleEmitter::getPos() const
{
	return this->mPos;
}

void ParticleEmitter::createShape(ID3D11DeviceContext* context)
{
	if (mParticles.size() >= MAX_PARTICLES_PER_EMITTER - 8000)
		return;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 20; k++)
			{
				Particle particle;

				particle.color = Vector3((rand() % 100) / 100.f, (rand() % 100) / 100.f, (rand() % 100) / 100.f);
				particle.pos = this->mPos;

				particle.lifeTime = 10;
				particle.velocity = Vector3(-1 + (i / 10.f), -1 + (j / 10.f), -1 + (k / 10.f));
				particle.velocity *= 0.003f;

				this->mParticles.push_back(particle);
			}
		}
	}

}
