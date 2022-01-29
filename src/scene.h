#pragma once

//A Scene should contain information about: Public: 1. Objects to be rendered, 2. Callbacks for objects that accept input?, Private: 3. Any state internal to the scene, IE the simulation
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
	Scene (Renderer &renderer);
	virtual ~Scene();
	
	//To be called by the context at the beginning of each frame
	void getRenderingStack(std::stack<Sprite*> &renderingStack);
	
	virtual void populateRenderingStack(std::stack<Sprite*> &renderingStack) = 0; //should be private
	
	//locked and unlocked on each loop of run(), should be locked before calling populateRenderingStack
	mutexQueue sync;
	
	//Runs updateInternalState, respecting simFrameDeltaMS, until stop.
	void run(void);
	bool stop = false;
	
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
