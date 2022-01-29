#include <renderer.h>

int Renderer::count = 0; //Has to be initialized here, instead of header.

Renderer::Renderer(Config &config)
{
	//In case more than one renderer is ever created
	if(!this->count) 
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) SDL_ERROR_EXIT();
		if(IMG_Init(IMG_INIT_PNG)   < 0) IMG_ERROR_EXIT();
	}
	this->count++;
	
	this->window =	SDL_CreateWindow("ParticleSim", 
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					config.video.windowWidth, config.video.windowHeight,
					config.video.windowType | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!window) SDL_ERROR_EXIT();
	
	renderer = SDL_CreateRenderer(window, -1, 
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if(!window) SDL_ERROR_EXIT();
	
	//surface = SDL_GetWindowSurface(window);
	
	windowArea.x = 0;
	windowArea.y = 0;
	windowArea.w = config.video.windowWidth;
	windowArea.h = config.video.windowHeight;
}

Renderer::~Renderer()
{
	//FIXME: Cleanup!
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
	//TODO: Wait for vsync, or otherwise time it.
	//SDL_Delay(5);//TEMPORARY
	SDL_RenderPresent(this->renderer);
	return;
}
/*
#include "SDL.h"

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    surface = SDL_LoadBMP("sample.bmp");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return 3;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return 3;
    }
    SDL_FreeSurface(surface);

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
*/
