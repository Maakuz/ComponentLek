#include "Game.h"

Game::Game(GraphicsHandler* gHandler)
{
	this->mGraphicsHandler = gHandler;
	gHandler->setupShaders();
	gHandler->setupDepthStencil();
	gHandler->setupLightHandler();
	gHandler->setupView(1280, 720);

	this->camOffset = DirectX::SimpleMath::Vector3(-10, 5, 0);

	this->createPlayer();
	this->createCamera();
	this->createGround();
	
	this->mEntities.push_back(player);
	this->mEntities.push_back(cameraEntity);
}

Game::~Game()
{
	for (int i = 0; i < this->mEntities.size(); i++)
	{
		delete this->mEntities[i];
	}
}

void Game::createPlayer()
{
	Mesh* playerMesh = new Mesh;
	playerMesh->loadMesh(this->createCube(0, 1, 0), this->mGraphicsHandler->getDevice());

	Velocity* vel = new Velocity(0.97f);

	TransformBuffer* buf = new TransformBuffer();
	buf->setupBuffer(this->mGraphicsHandler->getDevice());

	ParticleEmitter* emitter = new ParticleEmitter;

	emitter->setupBuffer(this->mGraphicsHandler->getDevice());
	emitter->createShape(this->mGraphicsHandler->getDeviceContext());

	this->player = new Entity;

	this->player->addComponent(new Position);
	this->player->addComponent(buf);
	this->player->addComponent(playerMesh);
	this->player->addComponent(vel);
	this->player->addComponent(new KeyboardMovement(0.001, vel));
	this->player->addComponent(emitter); 

	//TODO: HITBOX
}

void Game::createCamera()
{
	this->cameraEntity = new Entity;
	Camera* cam = new Camera(1280, 720);
	cam->setupBuffer(this->mGraphicsHandler->getDevice());

	DirectionalLight* light = new DirectionalLight(DirectX::SimpleMath::Vector3(0.5f, -0.5f, 0), DirectX::SimpleMath::Vector3(0.5f, 0.5f, 0.5f));
	this->AddDirLight(this->cameraEntity, light);

	this->cameraEntity->addComponent(new Position(this->camOffset.x, this->camOffset.y, this->camOffset.z));
	this->cameraEntity->addComponent(cam);
}

void Game::createGround()
{
	Mesh* meshWall = new Mesh;
	std::vector<Vertex> meshGroundVec;
	for (int i = 0; i < 10; i++)
	{
		std::vector<Vertex> vec = createCube(0.9f, 0.9f, 0.9f, 0, -2, -6 + (i * 2));

		meshGroundVec.insert(meshGroundVec.end(), vec.begin(), vec.end());
	}

	meshWall->loadMesh(meshGroundVec, this->mGraphicsHandler->getDevice());

	Entity* ground = new Entity;

	ground->addComponent(meshWall);

	this->mEntities.push_back(ground);

	//TODO: HITBOX


	
}

void Game::update(float deltaTime)
{
	//TODO: FAKTISKT GÖRA ETT SPEL
	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::velocity))
		{
			Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));
			Velocity* vel = dynamic_cast<Velocity*>(this->mEntities[i]->getComponent(ComponentID::velocity));
			
			if (this->mEntities[i]->hasComponent(ComponentID::keyboardInput))
			{
				KeyboardMovement* km = dynamic_cast<KeyboardMovement*>(this->mEntities[i]->getComponent(ComponentID::keyboardInput));
				km->update(deltaTime);
			}


			vel->applyFriction();

			pos->move(vel->getVelocity());
		}

		if (this->mEntities[i]->hasComponent(ComponentID::camera))
		{
			Camera* cam = dynamic_cast<Camera*>(this->mEntities[i]->getComponent(ComponentID::camera));
			Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));
			cam->setPos(pos->getPosition());
			cam->updateCamera(this->mGraphicsHandler->getDeviceContext());

			std::cout << pos->toString() << std::endl;
		}

		if (this->mEntities[i]->hasComponent(ComponentID::transformBuffer))
		{
			TransformBuffer* buffer = dynamic_cast<TransformBuffer*>(this->mEntities[i]->getComponent(ComponentID::transformBuffer));
			buffer->resetMatrix();
			//rotation before pos

			if (this->mEntities[i]->hasComponent(ComponentID::position))
			{
				Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));
				buffer->multiplyCurrent(pos->getTransformMatrix());
			}


			
			buffer->updateBuffer(this->mGraphicsHandler->getDeviceContext());
		}

		if (this->mEntities[i]->hasComponent(ComponentID::pointLight))
		{
			PointLight* light = dynamic_cast<PointLight*>(this->mEntities[i]->getComponent(ComponentID::pointLight));
			Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));

			light->setPos(pos->getPosition() + DirectX::SimpleMath::Vector3(0, 1, 0));
		}

		if (this->mEntities[i]->hasComponent(ComponentID::collisionBox))
		{
			CollisionBox* box1 = dynamic_cast<CollisionBox*>(this->mEntities[i]->getComponent(ComponentID::collisionBox));

			if (this->mEntities[i]->hasComponent(ComponentID::position))
			{
				Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));

				box1->setPosition(pos->getPosition());
			}

			for (int j = 0; j < this->mEntities.size(); j++)
			{
				if (this->mEntities[j]->hasComponent(ComponentID::collisionBox) && i != j)
				{
					CollisionBox* box2 = dynamic_cast<CollisionBox*>(this->mEntities[j]->getComponent(ComponentID::collisionBox));

					if (box1->intersects(*box2))
					{
						//TODO: någon form av intersection handling
					}
				}
			}
		}

		if (this->mEntities[i]->hasComponent(ComponentID::gravity))
		{
			Gravity* grav = dynamic_cast<Gravity*>(this->mEntities[i]->getComponent(ComponentID::gravity));
			Velocity* vel = dynamic_cast<Velocity*>(this->mEntities[i]->getComponent(ComponentID::velocity));

			vel->addYVelocity(-grav->getGravForce());

		}

		if (this->mEntities[i]->hasComponent(ComponentID::particleEmitter))
		{
			ParticleEmitter* emitter = dynamic_cast<ParticleEmitter*>(this->mEntities[i]->getComponent(ComponentID::particleEmitter));
			Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));

			emitter->setPosition(pos->getPosition());
			emitter->update(deltaTime, this->mGraphicsHandler->getDeviceContext());

			emitter->createShape(this->mGraphicsHandler->getDeviceContext());
		}
	}

	//Make camera follow player

	Position* camPos = dynamic_cast<Position*>(this->cameraEntity->getComponent(ComponentID::position));
	Position* playerPos = dynamic_cast<Position*>(this->player->getComponent(ComponentID::position));

	camPos->setPosition(playerPos->getPosition() + this->camOffset);


}

void Game::draw()
{
	this->mGraphicsHandler->clear();


	Camera* cam = dynamic_cast<Camera*>(this->cameraEntity->getComponent(ComponentID::camera));
	this->mGraphicsHandler->setVP(cam->getBuffer());
	this->mGraphicsHandler->setCamPos(cam->getPosBuffer());

	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::mesh))
			this->mGraphicsHandler->render(this->mEntities[i]);
	}

	for (size_t i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::particleEmitter))
			this->mGraphicsHandler->renderParticles(this->mEntities[i]);
	}

	this->mGraphicsHandler->present();
}

void Game::handleKeyPress(SDL_KeyboardEvent const& key)
{
	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::keyboardInput))
		{
			KeyboardMovement* km = dynamic_cast<KeyboardMovement*>(this->mEntities[i]->getComponent(ComponentID::keyboardInput));
			km->handleKeyPress(key);
		}
	}
}

void Game::handleKeyRelease(SDL_KeyboardEvent const& key)
{
	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::keyboardInput))
		{
			KeyboardMovement* km = dynamic_cast<KeyboardMovement*>(this->mEntities[i]->getComponent(ComponentID::keyboardInput));
			km->handleKeyRelease(key);
		}
	}
}

void Game::AddDirLight(Entity* entity, DirectionalLight* dirLight)
{
	entity->addComponent(dirLight);
	this->mGraphicsHandler->getLightHandler()->addDirectionalLight(dirLight);
}

void Game::AddPointLight(Entity* entity, PointLight* pointLight)
{
	entity->addComponent(pointLight);
	this->mGraphicsHandler->getLightHandler()->addPointLight(pointLight);
}

std::vector<Vertex> Game::createCube(float r, float g, float b, float x, float y, float z)
{
	using namespace DirectX::SimpleMath;
	//this was very annoying, it better be right.
	//This cube is fucked so far beyond coprehension
	Vertex cube[]
	{
		//front
		x + 1, y + 1, z + -1,
		0, 0, -1,
		r, g, b,
		
		x + -1, y + -1, z + -1,
		0, 0, -1,
		r, g, b,

		x + -1, y + 1, z + -1,
		0, 0, -1,
		r, g, b,


		x + -1, y + -1, z + -1,
		0, 0, -1,
		r, g, b,

		x + 1, y + 1, z + -1,
		0, 0, -1,
		r, g, b,

		x + 1, y + -1, z + -1,
		0, 0, -1,
		r, g, b,

		//back
		x + 1, y + 1, z + 1,
		0, 0, 1,
		r, g, b,

		x + -1, y + -1, z + 1,
		0, 0, 1,
		r, g, b,

		x + 1, y + -1, z + 1,
		0, 0, 1,
		r, g, b,


		
		x + -1, y + -1, z + 1,
		0, 0, 1,
		r, g, b,

		x + 1, y + 1, z + 1,
		0, 0, 1,
		r, g, b,
		
		x + -1, y + 1, z + 1,
		0, 0, 1,
		r, g, b,

		//top
		x + 1, y + 1,  z + 1,
		0, 1, 0,
		r, g, b,

		x + -1, y + 1,  z + -1,
		0, 1, 0,
		r, g, b,
		
		x + -1, y + 1, z + 1,
		0, 1, 0,
		r, g, b,


		
		x + -1, y + 1, z + -1,
		0, 1, 0,
		r, g, b,

		x + 1, y + 1, z + 1,
		0, 1, 0,
		r, g, b,
		
		x + 1, y + 1,  z + -1,
		0, 1, 0,
		r, g, b,

		//bottom
		x + 1, y + -1, z + 1,
		0, -1, 0,
		r, g, b,

		x + -1, y + -1, z + -1,
		0, -1, 0,
		r, g, b,
		
		x + 1, y + -1, z + -1,
		0, -1, 0,
		r, g, b,


		 
		x + -1, y + -1, z + -1,
		0, -1, 0,
		r, g, b,

		x + 1, y + -1, z + 1,
		0, -1, 0,
		r, g, b,
		
		x + -1, y + -1, z + 1,
		0, -1, 0,
		r, g, b,
		 
		//Left
		x + -1, y + 1, z + -1,
		-1, 0, 0,
		r, g, b,

		x + -1, y + -1, z + 1,
		-1, 0, 0,
		r, g, b,

		x + -1, y + 1, z + 1,
		-1, 0, 0,
		r, g, b,


		
		x + -1, y + -1, z + 1,
		-1, 0, 0,
		r, g, b,

		x + -1, y + 1, z + -1,
		-1, 0, 0,
		r, g, b,
		
		x + -1, y + -1, z + -1,
		-1, 0, 0,
		r, g, b,

		//Right
		x + 1, y + 1, z + 1,
		1, 0, 0,
		r, g, b,

		x + 1, y + -1, z + -1,
		1, 0, 0,
		r, g, b,

		x + 1, y + 1, z + -1,
		1, 0, 0,
		r, g, b,



		x + 1, y + -1, z + -1,
		1, 0, 0,
		r, g, b,

		x + 1, y + 1, z + 1,
		1, 0, 0,
		r, g, b,

		x + 1, y + -1, z + 1,
		1, 0, 0,
		r, g, b,
	};

	std::vector<Vertex> cubeVec;

	for (int i = 0; i < 36; i++)
	{
		cubeVec.push_back(cube[i]);
	}

	return cubeVec;
}
