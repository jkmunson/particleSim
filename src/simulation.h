#pragma once

#include <sprite.h>
#include <scene.h>
#include <renderer.h>
#include <errors.h>
#include <stdint.h>
#include <math.h>

#include <new>


class Bodies 
{
	public:
	explicit Bodies(void);
	~Bodies();
	
	void create(int64_t xvel, int64_t yvel, int64_t xpos, int64_t ypos, int64_t gravP);
	void print(SDL_Point ** points, int *cnt); //mallocs an array of points, size count, fills it with the points data, and then places that data at the pointers given.
	
	void accelerate(void);
	void move(void);
	
	private:
	int count;
	
	int64_t xVelocity[50];
	int64_t yVelocity[50];
	int64_t xPosition[50];
	int64_t yPosition[50];
	int64_t gravParameter[50];
};

class Simulation : public Scene
{
	public:
	explicit Simulation(Renderer &renderer);
	virtual ~Simulation();
	
	virtual void populateRenderingStack(std::stack<Sprite *> &renderingStack) override;
	virtual void updateInternalState(void) override;
	
	private:
	int height = 0;
	int direction = 1;
	
	Bodies bodies;
};
