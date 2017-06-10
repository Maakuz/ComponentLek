#include "Game.h"

Game::Game(GraphicsHandler* gHandler)
{
	this->mGraphicsHandler = gHandler;
}

Game::~Game()
{
}

void Game::update(float deltaTime)
{
}

void Game::draw()
{
	this->mGraphicsHandler->clear();
	this->mGraphicsHandler->render();
	this->mGraphicsHandler->present();
}
