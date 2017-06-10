#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "SimpleMath.h"
#include "Entity.h"

class Game
{
private:
	GraphicsHandler* mGraphicsHandler;

	std::vector<Entity*> mEntities;

public:
	Game(GraphicsHandler* gHandler);
	virtual ~Game();

	void update(float deltaTime);
	void draw();

	std::vector<Vertex> createCube();
};

#endif