#include <main.h>


int main(int argc, char** argv) 
{
	
	Config config(argc, argv);
	Renderer renderer(config);
	
	bool quit = false;
	SDL_Event event;
	while(!quit) {
		while(SDL_PollEvent(&event))
		{
			quit = (event.type == SDL_QUIT);
		}
		SDL_BlitScaled(renderer.splash, &renderer.windowArea, renderer.surface, &renderer.windowArea);
		SDL_UpdateWindowSurface(renderer.window);
		SDL_Delay(10);
	}
	
	return 0;
}
