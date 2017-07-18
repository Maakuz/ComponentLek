#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
	SDL_DestroyWindow(this->mWindow);
	SDL_Quit();
}

void Window::run(GraphicsHandler* gHandler)
{
	bool quit = false;

	SDL_Event e;
	Game game(gHandler);

	int64_t currentTime = SDL_GetPerformanceCounter();
	int64_t prevTime = 0;
	float deltaTime = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				game.handleKeyPress(e.key);
				break;

			case SDL_KEYUP:
				game.handleKeyRelease(e.key);
				break;
			}
			
		}

		prevTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();

		deltaTime = ((float)(currentTime - prevTime) / SDL_GetPerformanceFrequency()) * 1000;

		//std::cout << deltaTime << std::endl;
		SDL_Delay(1);



		game.update(deltaTime);
		game.draw();
		
	}

}

void Window::setupWindow(int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);

	this->mWindow = SDL_CreateWindow(
		"Title",
		200,
		100,
		width,
		height,
		SDL_WINDOW_OPENGL
	);

	if (this->mWindow == NULL)
		exit(-1);

}
