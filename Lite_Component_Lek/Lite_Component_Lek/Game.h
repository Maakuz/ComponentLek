#ifndef GAME_H
#define GAME_H
#include "GraphicsHandler.h"

class Game
{
private:
	GraphicsHandler* mGraphicsHandler;

public:
	Game(GraphicsHandler* gHandler);
	virtual ~Game();

	void update(float deltaTime);
	void draw();
};

#endif