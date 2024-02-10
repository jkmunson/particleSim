#include <simulation.h>
#include <math.h>
#include <stdbool.h>

Simulation::Simulation(Renderer &renderer) 
: Scene(renderer)
{
	simFrameDeltaMs = 5;
	issim=true;
}

Simulation::~Simulation()
{
	
}

void Simulation::populateRenderingStack(std::stack<Sprite *> &renderingStack) 
{
	//renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{50,250,80,55}, 0, height, rendererRef.windowArea.w-2 , rendererRef.windowArea.h - height) );
	if(bodies.count>1) {
		SDL_Point *p;
		int count;
		bodies.print(&p,&count);
		renderingStack.push( new Points(SDL_BLENDMODE_BLEND, Color{255,255,255,255}, p,count) );
	}
	printf("Count: %i\n \033[F \r", bodies.count);
}

void Simulation::updateInternalState(void)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
		break;
		
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
				bodies.create(0,0,event.button.x*100000, event.button.y*100000, 5000000000);
			if(event.button.button == SDL_BUTTON_RIGHT)
				bodies.create(0,140,event.button.x*100000, event.button.y*100000, 40000000);
		break;
		
		case SDL_MOUSEBUTTONUP:
			//if(event.button.button == SDL_BUTTON_LEFT)
				//bodies.create(0,0,event.button.x*100000, event.button.y*100000, 4);
			if(event.button.button == SDL_BUTTON_RIGHT)
				bodies.create(0,-140,event.button.x*100000, event.button.y*100000, 40000000);
				
		case SDL_MOUSEMOTION:
		
		break;
		
		case SDL_MOUSEWHEEL:
			int x,y;
			SDL_GetMouseState(&x, &y);
			bodies.create(0,event.wheel.y*180,x*100000, y*100000, 5000000);
		break;
		
		default:
			//printf("Unhandeled Event %i\n", event.type);
		break;
		}
	}
	if(bodies.count>2) 
	{
		for(int i = 0; i<100; i++)
		{
			
		bodies.accelerate();
		bodies.move();
		}
	}
	
	height += direction;
	if((height > (rendererRef.windowArea.h - 2)) || height < 0) direction = (-1)*direction;
	
}

//###### Movement of the stellar bodies
	
Bodies::Bodies(void)
{
	
}

Bodies::~Bodies()
{
	
}

void Bodies::accelerate(void)
{
	//Initially, just a naiive implementation of gravity
	int cnt = count-1; // Last element of the array will already be complete when we arrive
	for(int i=0; i<cnt; i++)
	{
		if(!isValid(i)) continue; //Deleted Element
		for(int j=i+1; j<count; j++) 
		{ //Iterate over all elements further in the array, computing their pair of interractions
			if (!isValid(j)) continue; //Deleted Element
			double x = xPosition[i] - xPosition[j];
			double y = yPosition[i] - yPosition[j];
			//printf("x %li y%li\n", x, y);
			
			long double rsquaretemp = (long double)x*(long double)x + (long double)y*(long double)y;
			if (fabs(x)<30000 && fabs(y)<30000)
			{ //collision. Perfectly elastic
				double xMomentum = gravParameter[i]*xVelocity[i] + gravParameter[j]*xVelocity[j];
				double yMomentum = gravParameter[i]*yVelocity[i] + gravParameter[j]*yVelocity[j];
				gravParameter[i] = gravParameter[i] + gravParameter[j];
				xVelocity[i] = xMomentum/gravParameter[i];
				yVelocity[i] = yMomentum/gravParameter[i];
				gravParameter[j] = 0.; //delete it
				xVelocity[j] = NAN;
				continue;
			}
			
			double r = sqrtl((long double)rsquaretemp);
			double rsquare = rsquaretemp;
			double sin = y/r;
			double cos = x/r;
			xVelocity[i] -= (gravParameter[j]*cos)/rsquare;
			yVelocity[i] -= (gravParameter[j]*sin)/rsquare;
			xVelocity[j] += (gravParameter[i]*cos)/rsquare;
			yVelocity[j] += (gravParameter[i]*sin)/rsquare;
			
		}
	}
}

void Bodies::move(void)
{
	for(int i=0; i<count; i++) 
	{
		xPosition[i] += xVelocity[i];
		yPosition[i] += yVelocity[i];
	}
}

void Bodies::create(double xvel, double yvel, double xpos, double ypos, double gravP)
{
	xVelocity[count] = xvel;
	yVelocity[count] = yvel;
	xPosition[count] = xpos;
	yPosition[count] = ypos;
	gravParameter[count] = gravP;
	count++;
}

void Bodies::print(SDL_Point ** points, int *cnt)
{
	*points = (SDL_Point *)malloc(sizeof(**points)*count*5);
	int skips = 0;
	for(int i=0; i<count*5; i=i+5)
	{
		if(!isValid(i/5))
		{ //Don't do deleted elements
			skips += 5;
			continue;
		}
		(*points)[i-skips].x = xPosition[i/5]/100000;
		(*points)[i-skips].y = yPosition[i/5]/100000;
		
		(*points)[i+1-skips].x = (xPosition[i/5]/100000+1);
		(*points)[i+1-skips].y = (yPosition[i/5]/100000);
		
		(*points)[i+2-skips].x = (xPosition[i/5]/100000-1);
		(*points)[i+2-skips].y = (yPosition[i/5]/100000);
		
		(*points)[i+3-skips].x = (xPosition[i/5]/100000);
		(*points)[i+3-skips].y = (yPosition[i/5]/100000+1);
		
		(*points)[i+4-skips].x = (xPosition[i/5]/100000);
		(*points)[i+4-skips].y = (yPosition[i/5]/100000-1);
	}
	
	*cnt = (count*5)-skips;
}

bool Bodies::isValid(int id) 
{
	if (isnan(xPosition[id]) || isinf(xPosition[id])) return false;
	if (isnan(yPosition[id]) || isinf(yPosition[id])) return false;
	if (isnan(xVelocity[id]) || isinf(xVelocity[id])) return false;
	if (isnan(yVelocity[id]) || isinf(yVelocity[id])) return false;
	if (isnan(gravParameter[id]) || isinf(gravParameter[id] || gravParameter[id] < 100.)) return false;
	return true;
}
