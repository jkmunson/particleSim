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
	int direction = 1;
	uint8_t blue = 0;
	
	struct Button {
		char	name[30];
		int		x,y,w,h;
	};
	Button startButton = {"Start",10,10,130,50};
	bool startState = 0;
		
};
