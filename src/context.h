#pragma once
/*!
 *  Context is, essentially, the state machine of the program that
 *  coordinates all the working parts within one window.
 * 
 * The context brokers program and information flow between multiple scenes and rendering.
 * 
 */
#include <config.h>
#include <renderer.h>
#include <scene.h>
#include <sprite.h>
#include <errors.h> //TODO: Is this used here?
#include <mainMenu.h>

#include <stack>
#include <thread>


class Context
{
	public:
	explicit Context(Config &config, Renderer &renderer, Scene *initialScene); //A config object contains the information needed to initialize a context.
	~Context();
	
	Config &configRef; //We need to refer back to the configuration occasionally.
	
	std::stack<Scene *> activeScene; //The currently active scene that should be rendered.
	
	std::stack<Sprite *> renderingStack; //Buffer for items to be rendered, passed back and forth between the renderer and scenes
	
	//The renderer attached to this context
	Renderer &rendererRef;
	
	void run(void);
	
	private:
	//Clears the event queue, returns true if an SDL_QUIT events was found.
	bool flushEvents(void);
};
