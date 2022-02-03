#include <scene.h>

Scene::Scene(Renderer &renderer)
:rendererRef{renderer}
{}

Scene::~Scene()
{}

void Scene::delayFrameForDelta(void) 
{
	Uint64 currentDelta = SDL_GetPerformanceCounter() - simFrameLast;
	Uint64 desiredDelta = (simFrameDeltaMs * SDL_GetPerformanceFrequency()) / 1000;
	
	if(currentDelta < desiredDelta) 
	{
		SDL_Delay((desiredDelta - currentDelta)/(SDL_GetPerformanceFrequency()/1000));
	} else {
		std::cout << "Frame Lagged\n";
	}
	simFrameLast = SDL_GetPerformanceCounter();
}

void Scene::run(void) 
{
	while(!stop) {
		delayFrameForDelta();
		sync.lock();
		updateInternalState();
		sync.unlock();
	}
}


void Scene::getRenderingStack(std::stack<Sprite*> &renderingStack)
{
	sync.lock();
	populateRenderingStack(renderingStack);
	sync.unlock();
}
