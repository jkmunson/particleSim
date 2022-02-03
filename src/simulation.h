#pragma once

#include <sprite.h>
#include <scene.h>
#include <renderer.h>
#include <errors.h>

#include <new>


class Simulation : public Scene
{
	public:
	explicit Simulation(Renderer &renderer);
	virtual ~Simulation();
	
	virtual void populateRenderingStack(std::stack<Sprite *> &renderingStack) override;
	virtual void updateInternalState(void) override;
	
	private:
	int height = 0;
	int direction;
};
