#include <context.h>

//If initialScene is NULL, create the main menu!
Context::Context(Config &config, Renderer &renderer, Scene *initialScene)
:configRef{config}, rendererRef{renderer}
{
	
	if(initialScene)
	{
		activeScene.push(initialScene);
	} else {
		activeScene.push(new MainMenu(rendererRef));
	}
};

Context::~Context()
{
	while(!activeScene.empty())
	{
		delete activeScene.top();
		activeScene.pop();
	}
}

void Context::run(void)
{
	std::thread sceneThread([&](){activeScene.top()->run();}); //Lambda syntax already sucks.
	
	//Uint64 last = SDL_GetTicks64();
	bool quit = false;
	SDL_Event event;
	while(!quit) {
		while(SDL_PollEvent(&event))
		{
			quit = (event.type == SDL_QUIT);
		}
		activeScene.top()->getRenderingStack(renderingStack);
		rendererRef.drawScene(renderingStack);
		rendererRef.swapFrameBuffer();
		
		//std::cout << "FrameTime(ms):" << (SDL_GetTicks64() - last) <<"\n";
		//last = SDL_GetTicks64();
	}
	activeScene.top()->stop = true;
	sceneThread.join();
}
