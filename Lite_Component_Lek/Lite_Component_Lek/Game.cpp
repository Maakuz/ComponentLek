#include "Game.h"

Game::Game(GraphicsHandler* gHandler)
{
	this->mGraphicsHandler = gHandler;
	gHandler->setupShaders();
	gHandler->setupDepthStencil();
	gHandler->setupLightHandler();
	gHandler->setupView(1280, 720);
	Entity* floorEntity = new Entity;
	Entity* wallEntity = new Entity;
	Entity* cameraEntity = new Entity;
	Entity* lightEntity = new Entity;

	Mesh* meshWall = new Mesh;
	std::vector<Vertex> meshWallVec;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::vector<Vertex> vec = createCube(0.9f, 0.9f, 0.9f, 10, -2 + j * 2, i * 2);

			meshWallVec.insert(meshWallVec.end(), vec.begin(), vec.end());
		}
	}

	meshWall->loadMesh(meshWallVec, gHandler->getDevice());
	wallEntity->addComponent(meshWall);

	floorEntity->addComponent(new Position());
	
	Mesh* mesh = new Mesh;
	std::vector<Vertex> meshVec;
	for (int i = 0; i < 10; i++)
	{
		std::vector<Vertex> vec = createCube(0.9f, 0.9f, 0.9f, 0.5f + (i * 2), -2);

		meshVec.insert(meshVec.end(), vec.begin(), vec.end());
	}

	mesh->loadMesh(meshVec, gHandler->getDevice());

	Velocity* vel = new Velocity(0.97f);

	Camera* cameraCom = new Camera(1280, 720);
	cameraCom->setupBuffer(this->mGraphicsHandler->getDevice());

	Position* pos = new Position();
	pos->setPosition(DirectX::SimpleMath::Vector3(-10, 10, 0));

	TransformBuffer* transform = new TransformBuffer;
	transform->setupBuffer(this->mGraphicsHandler->getDevice());

	floorEntity->addComponent(mesh);

	cameraEntity->addComponent(pos);
	cameraEntity->addComponent(cameraCom);

	lightEntity->addComponent(new Position());

	this->AddPointLight(lightEntity, new PointLight(10, DirectX::SimpleMath::Vector3(0, 3, 0)));
	
	lightEntity->addComponent(transform);

	lightEntity->addComponent(vel);

	lightEntity->addComponent(new KeyboardMovement(0.001f));

	mesh = new Mesh;
	mesh->loadMesh(createCube(0, 1, 0), this->mGraphicsHandler->getDevice());
	lightEntity->addComponent(mesh);

	this->AddDirLight(floorEntity, new DirectionalLight(DirectX::SimpleMath::Vector3(0.3f, 0.7f, 0)));
	this->AddDirLight(cameraEntity, new DirectionalLight(DirectX::SimpleMath::Vector3(0.3f, 0.7f, 0)));

	mEntities.push_back(floorEntity);
	mEntities.push_back(lightEntity);
	mEntities.push_back(wallEntity);


	

	
	
	mEntities.push_back(cameraEntity);

}

Game::~Game()
{
	for (int i = 0; i < this->mEntities.size(); i++)
	{
		delete this->mEntities[i];
	}
}

void Game::update(float deltaTime)
{
	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::velocity))
		{
			Position* pos = dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position));
			Velocity* vel = dynamic_cast<Velocity*>(this->mEntities[i]->getComponent(ComponentID::velocity));
			
			if (this->mEntities[i]->hasComponent(ComponentID::keyboardInput))
			{
				KeyboardMovement* km = dynamic_cast<KeyboardMovement*>(this->mEntities[i]->getComponent(ComponentID::keyboardInput));
				vel->addVelocity(km->getSpeed());
			}


			vel->applyFriction();

			pos->move(vel->getVelocity());
		}

		if (this->mEntities[i]->hasComponent(ComponentID::camera))
		{
			Camera* cam = dynamic_cast<Camera*>(this->mEntities[i]->getComponent(ComponentID::camera));
			cam->setPos(dynamic_cast<Position*>(this->mEntities[i]->getComponent(ComponentID::position))->getPosition());
			cam->updateCamera(this->mGraphicsHandler->getDeviceContext());
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

	}
}

void Game::draw()
{
	this->mGraphicsHandler->clear();

	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::camera))
		{
			Camera* cam = dynamic_cast<Camera*>(this->mEntities[i]->getComponent(ComponentID::camera));
			this->mGraphicsHandler->setVP(cam->getBuffer());
		}
	}

	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::mesh))
			this->mGraphicsHandler->render(this->mEntities[i]);
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
			Velocity* vel = dynamic_cast<Velocity*>(this->mEntities[i]->getComponent(ComponentID::velocity));
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
