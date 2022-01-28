#pragma once
#include <stack>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <config.h>
#include <errors.h>
#include <sprite.h>



class Renderer{
	public:
	explicit Renderer(Config &config);
	~Renderer();
	
	void drawScene(std::stack<Sprite *> &renderingStack);
	void swapFrameBuffer(void);
	
	//TODO: Public or private...?
	SDL_Window 		*window;
	SDL_Renderer 	*renderer;
	//SDL_Surface 	*surface;
	SDL_Event 		event;
	SDL_Rect 		windowArea; //public

	//! If more than one window and renderer was created, this tracks how many so SDL_Quit isn't called too soon.
	static int count;
}; 
