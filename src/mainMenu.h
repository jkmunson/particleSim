#pragma once

#include <sprite.h>
#include <input.h>
#include <scene.h>
#include <renderer.h>
#include <errors.h>

#include <new>

class MainMenu : public Scene
{
	public:
	explicit MainMenu(Renderer &renderer);
	virtual ~MainMenu();
	
	virtual void populateRenderingStack(std::stack<Sprite *> &renderingStack) override;
	virtual void updateInternalState(void) override;
	
	private:
	SDL_Texture		*splash;
	int height = 0;
};
