#pragma once

//A Scene should contain information about: Public: 1. Objects to be rendered, 2. Callbacks for objects that accept input?, Private: 3. Any state internal to the scene, IE the simulation
//A scene will be "worked on" twice each frame, ie [pre-rendering(Take input?)] -> [concurrent to rendering] where the rendering list will be locked - a good time to perform simulation integration!
#include <sprite.h>
#include <renderer.h>

#include <vector>
#include <stack>


class Scene
{
	public:
	Scene (Renderer &renderer);
	virtual ~Scene();
	//To be called by the context at the beginning of each frame
	virtual void populateRenderingStack(std::stack<Sprite*> &renderingStack) = 0;
	
	//To be called by the context after the renderer has begun it's work
	virtual void updateInternalState(void) = 0;
	
	//Being able to query renderer for information, like the screen width or the window surface format, is nescessary.
	Renderer &rendererRef;
	
};
