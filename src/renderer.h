#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <config.h>
#include <errors.h>

class Renderer{
	public:
	Renderer(Config &config);
	~Renderer();
	
	//TODO: Public or private...?
	SDL_Window 		*window;
    SDL_Renderer 	*renderer;
    SDL_Surface 	*surface;
    SDL_Texture 	*texture;
    SDL_Event 		event;
    SDL_Rect 		windowArea;
    
    SDL_Surface *splash;
    
    //! If more than one window and renderer was created, this tracks how many so SDL_Quit isn't called too soon.
	static int count;
}; 
