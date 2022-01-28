#include <context.h>

//If initialScene is NULL, create the main menu!
Context::Context(Config &config, Renderer &renderer, Scene *initialScene)
:configRef{config}, rendererRef{renderer}
{
	
	if(initialScene)
	{
		activeScene.push(initialScene);
	} else {
		activeScene.push(new MainMenu(rendererRef));
	}
};

Context::~Context()
{
	while(!activeScene.empty())
	{
		delete activeScene.top();
		activeScene.pop();
	}
}

void Context::run(void)
{
	activeScene.top()->populateRenderingStack(renderingStack);
	rendererRef.drawScene(renderingStack);
	rendererRef.swapFrameBuffer();
	activeScene.top()->updateInternalState();
}
