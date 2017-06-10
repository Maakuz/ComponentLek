#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <iostream>
#include "Game.h"

class Window
{
private:
	SDL_Window* mWindow;

public:
	Window();
	virtual ~Window();

	void run(GraphicsHandler* gHandler);

	void setupWindow(int width, int height);
};


#endif