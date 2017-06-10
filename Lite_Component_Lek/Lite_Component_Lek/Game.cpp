#include "Game.h"

Game::Game(GraphicsHandler* gHandler)
{
	this->mGraphicsHandler = gHandler;
	gHandler->setupShaders();
	gHandler->setupView(1280, 720);
	Entity* test = new Entity;
	Mesh* mesh = new Mesh;

	mesh->loadMesh(createCube(), gHandler->getDevice());

	test->addComponent(mesh);

	mEntities.push_back(test);
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
}

void Game::draw()
{
	this->mGraphicsHandler->clear();

	for (int i = 0; i < this->mEntities.size(); i++)
	{
		if (this->mEntities[i]->hasComponent(ComponentID::mesh))
			this->mGraphicsHandler->render(this->mEntities[i]);
	}

	this->mGraphicsHandler->present();
}

std::vector<Vertex> Game::createCube()
{
	using namespace DirectX::SimpleMath;
	//this was very annoying, it better be right.
	Vertex cube[]
	{
		//front
		-1, -1, -1,
		1, 1, 1,

		1, 1, -1,
		1, 1, 1,

		-1, 1, -1,
		1, 1, 1,


		1, 1, -1,
		1, 1, 1,

		-1, -1, -1,
		1, 1, 1,

		1, -1, -1,
		1, 1, 1,

		//back
		-1, -1, 1,
		1, 1, 1,

		1, 1, 1,
		1, 1, 1,

		1, -1, 1,
		1, 1, 1,



		1, 1, 1,
		1, 1, 1,
		
		-1, -1, 1,
		1, 1, 1,
		
		-1, 1, 1,
		1, 1, 1,

		//top
		-1, 1, -1,
		1, 1, 1,

		1, 1, 1,
		1, 1, 1,
		
		-1, 1, 1,
		1, 1, 1,



		1, 1, 1,
		1, 1, 1,
		
		-1, 1, -1,
		1, 1, 1,
		
		1, 1, -1,
		1, 1, 1,

		//bottom
		-1, -1, -1,
		1, 1, 1,

		1, -1, 1,
		1, 1, 1,
		
		1, -1, -1,
		1, 1, 1,



		1, -1, 1,
		1, 1, 1,
		
		-1, -1, -1,
		1, 1, 1,
		
		-1, -1, 1,
		1, 1, 1,

		//Left
		-1, -1, 1,
		1, 1, 1,
		
		-1, 1, -1,
		1, 1, 1,
		
		-1, 1, 1,
		1, 1, 1,



		-1, 1, -1,
		1, 1, 1,
		
		-1, -1, 1,
		1, 1, 1,
		
		-1, -1, -1,
		1, 1, 1,

		//Right
		1, -1, -1,
		1, 1, 1,
		
		1, 1, 1,
		1, 1, 1, 
			
		1, 1, -1,
		1, 1, 1,



		1, 1, 1,
		1, 1, 1,

		1, -1, -1,
		1, 1, 1,

		1, -1, 1,
		1, 1, 1
	};

	std::vector<Vertex> cubeVec;

	for (int i = 0; i < 36; i++)
	{
		cubeVec.push_back(cube[i]);
	}

	return cubeVec;
}
