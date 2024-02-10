#pragma once

#include <sprite.h>
#include <scene.h>
#include <renderer.h>
#include <errors.h>
#include <stdint.h>
#include <math.h>
#include <cmath>

#include <new>


class Bodies 
{
	public:
	explicit Bodies(void);
	~Bodies();
	
	void create(double xvel, double yvel, double xpos, double ypos, double gravP);
	void print(SDL_Point ** points, int *cnt); //mallocs an array of points, size count, fills it with the points data, and then places that data at the pointers given.
	
	void accelerate(void);
	void move(void);
	
	int count=0;
	private:
	double xVelocity[5000];
	double yVelocity[5000];
	double xPosition[5000];
	double yPosition[5000];
	double gravParameter[5000];
	
	bool isValid(int id);
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
