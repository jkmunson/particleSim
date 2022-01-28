#pragma once
/*!
 *  Context is, essentially, the state machine of the program that
 *  coordinates all the working parts within one window.
 * 
 * The context brokers program flow between Input, Scenes, and rendering.
 * 
 */
#include <config.h>
#include <renderer.h>
#include <scene.h>
#include <sprite.h>
#include <errors.h> //TODO: If this used here?
#include <mainMenu.h>

#include <stack>


class Context
{
	public:
	explicit Context(Config &config, Renderer &renderer, Scene *initialScene); //A config object contains the information needed to initialize a context.
	~Context();
	
	//The context
	Config &configRef;
	std::stack<Scene *> activeScene; //The currently active scene that should receive input, and should be rendered.
	
	std::stack<Sprite *> renderingStack;
	
	//The functional objects attached to this context
	Renderer &rendererRef;
	
	void run(void);
};
