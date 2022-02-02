#include <renderer.h>

int Renderer::count = 0; //Has to be initialized here, instead of header.

Renderer::Renderer(const char *windowName, Config &config)
{
	//In case more than one renderer is ever created
	if(!count) 
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0) SDL_ERROR_EXIT();
		if(IMG_Init(IMG_INIT_PNG)   < 0) IMG_ERROR_EXIT();
	}
	count++;
	
	window =	SDL_CreateWindow(windowName, 
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					config.video.windowWidth, config.video.windowHeight,
					config.video.windowType | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!window) SDL_ERROR_EXIT();
	renderer = SDL_CreateRenderer(window, -1, 
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if(!window) SDL_ERROR_EXIT();
	
	windowArea.x = 0;
	windowArea.y = 0;
	windowArea.w = config.video.windowWidth;
	windowArea.h = config.video.windowHeight;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window); //MYSTERY: Commenting out this line doesn't upset valgrind.
	
	count--;
	if(!count) {
		SDL_Quit();
	}
}

void Renderer::drawScene(std::stack<Sprite*> &renderingStack)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	
	while(!renderingStack.empty())
	{
		SDL_SetRenderDrawBlendMode(renderer, renderingStack.top()->blending);
		renderingStack.top()->draw(renderer);
		delete renderingStack.top();
		renderingStack.pop();
		if(renderingStack.empty()) break;
	}
}

void Renderer::swapFrameBuffer(void)
{
	//RendererPresent will wait for vsync
	SDL_RenderPresent(this->renderer);
	return;
}
