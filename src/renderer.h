#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <config.h>

class Renderer{
	public:
	Renderer(Config &config);
	~Renderer();
	
	//TODO: ublic or private...?
	SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
	
	private:
	//! If more than one window and renderer was created, this tracks how many so SDL_Quit isn't called too soon.
	static int rendererCount;
}
Renderer::rendererCount = 0; //TODO: Can this be initialized inside the class definition?
