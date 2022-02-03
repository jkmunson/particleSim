#pragma once
//A scene will be "worked on" twice each frame, ie [pre-rendering(Take input?)] -> [concurrent to rendering] where the rendering list will be locked - a good time to perform simulation integration!
#include <sprite.h>
#include <renderer.h>
#include <mutexQueue.h>

#include <vector>
#include <stack>
#include <stdint.h>
#include <thread>
#include <atomic>
#include <mutex>


class Scene
{
	public:
	//Access to the target renderer object is needed to create the scene - to create textures in the correct format, and get the window size etc.
	Scene (Renderer &renderer);
	virtual ~Scene();
	
	//To be called by the context at the beginning of each frame
	void getRenderingStack(std::stack<Sprite*> &renderingStack);
	
	//To be called by the context, to run in it's own thread until stop is set.
	void run(void);
	bool stop = false;// Set by context, read by scene
	
	bool quit = false;// Sey by scene, causes program to end
	
	bool pushScene = false; //Set by scene, cleared by context
	Scene *nextScene = NULL; //Set by scene, cleared by context
	bool popScene = false; //Set by scene, cleared by context
	
	bool issim = false;
	
	protected:
	virtual void populateRenderingStack(std::stack<Sprite*> &renderingStack) = 0;
	
	//locked and unlocked on each loop of run(), should be locked before calling populateRenderingStack
	mutexQueue sync;
	
	//Runs updateInternalState, respecting simFrameDeltaMS, until stop.
	
	//Run once per simulation frame
	virtual void updateInternalState(void) = 0; //should be private
	
	//Timing of when the frame should be calculated
	void delayFrameForDelta(void); 
	
	//Being able to query renderer for information, like the screen width or the window surface format, is nescessary.
	Renderer &rendererRef;
	
	//Determines timing of the simulation function
	Uint64 simFrameDeltaMs = 33; //Default to 30hz simulation. Change in derived classes.
	Uint64 simFrameLast = 0;
};
