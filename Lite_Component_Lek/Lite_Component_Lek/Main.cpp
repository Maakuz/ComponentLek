#include <crtdbg.h>
#include "Window.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Window window;
	GraphicsHandler gHandler;

	window.setupWindow(200, 200);
	gHandler.setup3DContent();

	window.run(&gHandler);

	return 0;
}