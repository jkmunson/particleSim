#include <main.h>


int main(int argc, char** argv) 
{
	
	Config config(argc, argv);
	Renderer renderer(config);
	Context context(config, renderer, NULL);
	
	
	Uint64 last = SDL_GetTicks64();
	bool quit = false;
	SDL_Event event;
	while(!quit) {
		while(SDL_PollEvent(&event))
		{
			quit = (event.type == SDL_QUIT);
		}
		context.run();
		
		std::cout << "FrameTime(ms):" << (SDL_GetTicks64() - last) <<"\n";
		last = SDL_GetTicks64();
	}
	
	return 0;
}
