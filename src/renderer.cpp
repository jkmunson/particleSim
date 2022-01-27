#include <renderer.h>

int Renderer::count = 0; //Has to be initialized here, instead of header.

Renderer::Renderer(Config &config)
{
	//In case more than one renderer is ever created
	if(!this->count) 
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0) SDL_ERROR_EXIT();
		if(IMG_Init(IMG_INIT_PNG)   < 0) IMG_ERROR_EXIT();
	}
	this->count++;
	if(	SDL_CreateWindowAndRenderer(
		config.video.windowWidth, 
		config.video.windowHeight, 
		config.video.windowType | SDL_WINDOW_SHOWN, 
		&this->window, 
		&this->renderer)
	) SDL_ERROR_EXIT();
	
	this->surface = SDL_GetWindowSurface(this->window);
	
	SDL_SetWindowTitle(this->window, "ParticleSim");
	
	{
		SDL_Surface *temp = IMG_Load("data/img/splash2.png");
		if(!temp) IMG_ERROR_EXIT();
		this->splash = SDL_ConvertSurface(temp, this->surface->format, 0);
		if(!this->splash) SDL_ERROR_EXIT();
		SDL_FreeSurface(temp);
	}
	this->windowArea.x = 0;
	this->windowArea.y = 0;
	this->windowArea.w = config.video.windowWidth;
	this->windowArea.h = config.video.windowHeight;
	//TODO: Spawn Rendering Thread
	
}

Renderer::~Renderer()
{
	//TODO: Cleanup!
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
