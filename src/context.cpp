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
	std::thread sceneThread([&](){activeScene.top()->run();}); //Lambda syntax sucks.
	
	//Uint64 last = SDL_GetTicks64();
	while(!activeScene.top()->quit) 
	{
		if(activeScene.top()->pushScene) 
		{
			activeScene.top()->stop = true;
			sceneThread.join();
			activeScene.top()->pushScene = false;
			Scene *temp = activeScene.top()->nextScene;
			activeScene.top()->nextScene = NULL;
			activeScene.push(temp);
			if(flushEvents()) return;
			std::thread sceneThread([&](){activeScene.top()->run();});
			printf("Scene Pushed\n");
			while(1);
		}
		if(activeScene.top()->popScene) 
		{
			activeScene.top()->stop = true;
			sceneThread.join();
			delete activeScene.top();
			activeScene.pop();
			if(activeScene.empty()) return; //This context no longer has a scene to run!
			if(flushEvents()) return;
			std::thread sceneThread([&](){activeScene.top()->run();});
		}
		while(activeScene.top()->issim){};
		printf("getting rendering stack\n");
		std::cout << std::flush;
		activeScene.top()->getRenderingStack(renderingStack);
		printf("Here\n got rendering stack\n");
		rendererRef.drawScene(renderingStack);
		rendererRef.swapFrameBuffer();
		
		//std::cout << "FrameTime(ms):" << (SDL_GetTicks64() - last) <<"\n";
		//last = SDL_GetTicks64();
	}
	activeScene.top()->stop = true;
	sceneThread.join();
}

bool Context::flushEvents(void)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		printf("Event: %i flushed.\n",event.type);
		if (event.type == SDL_QUIT) return true;
	}
	return false;
}
