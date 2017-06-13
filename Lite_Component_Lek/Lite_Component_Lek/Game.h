#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"
#include "SimpleMath.h"
#include "Entity.h"
#include "Camera.h"
#include "Velocity.h"
#include "Position.h"
#include "KeyboardMovement.h"
#include "TransformBuffer.h"
#include "DirectionalLight.h"

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

	void handleKeyPress(SDL_KeyboardEvent const &key);
	void handleKeyRelease(SDL_KeyboardEvent const &key);

	void AddDirLight(Entity* entity, DirectionalLight* dirLight);

	std::vector<Vertex> createCube(float r, float g, float b, float x = 0, float y = 0, float z = 0);
};

#endif