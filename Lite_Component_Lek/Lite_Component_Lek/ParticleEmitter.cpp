#include "ParticleEmitter.h"
using namespace DirectX::SimpleMath;

ParticleEmitter::ParticleEmitter(Vector3 pos) : Component(ComponentID::particleEmitter)
{
	this->mPos = pos;
	this->mParticles.reserve(MAX_PARTICLES_PER_EMITTER);
	this->mParticleInfos.reserve(MAX_PARTICLES_PER_EMITTER);
}

ParticleEmitter::~ParticleEmitter()
{
}

void ParticleEmitter::setupBuffer(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	data.pSysMem = mParticles.data();

	this->mBuffer.setupVertexBuffer(MAX_PARTICLES_PER_EMITTER * sizeof(Particle), data, true, device);
}

void ParticleEmitter::update(float dt, ID3D11DeviceContext* context)
{
	for (size_t i = 0; i < this->mParticles.size(); i++)
	{
		this->mParticles[i].pos  += (this->mParticleInfos[i].velocity * dt);
		this->mParticleInfos[i].lifeTime -= dt;
		//TODO: Remove if dead
	}
	if (!this->mParticles.empty())
		this->mBuffer.updateBuffer(sizeof(Particle) * this->mParticles.size(), &this->mParticles[0], context);
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
				ParticleInfo info;

				particle.color = Vector3((rand() % 100) / 100.f, (rand() % 100) / 100.f, (rand() % 100) / 100.f);
				particle.pos = this->mPos;

				info.lifeTime = 10;
				info.velocity = Vector3(-1 + (i / 10.f), -1 + (j / 10.f), -1 + (k / 10.f));
				info.velocity *= 0.003f;

				this->mParticles.push_back(particle);
				this->mParticleInfos.push_back(info);
			}
		}
	}

	

	this->mBuffer.updateBuffer(sizeof(Particle) * this->mParticles.size(), &this->mParticles[0], context);
}
