#include <simulation.h>

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
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,250,250,255}, 0, height, rendererRef.windowArea.w-2 , rendererRef.windowArea.h - height) );
	if(bodies.count>3) {
		SDL_Point *p;
		int count;
		bodies.print(&p,&count);
		renderingStack.push( new Points(SDL_BLENDMODE_BLEND, Color{250,250,250,255}, p,count) );
	}
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
			bodies.create(10,10,event.button.x*1000, event.button.y*1000, 10);
			printf("Created!\n");
		break;
		
		case SDL_MOUSEMOTION:
		
		break;
		
		default:
			//printf("Unhandeled Event %i\n", event.type);
		break;
		}
	}
	if(bodies.count>20) {
	bodies.accelerate();
	bodies.move();
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
		for(int j=i+1; j<count; j++) { //Iterate over all elements further in the array, computing their pair of interractions
			
			int64_t x = xPosition[count] - xPosition[j];
			int64_t y = yPosition[count] - yPosition[j];
			
			int64_t rsquare = x*x + y*y;
			double r = std::sqrt((double)rsquare);
			
			float sin = y/r;
			float cos = x/r;
			
			xVelocity[i] -= (long double)gravParameter[j]*cos;
			yVelocity[i] -= (long double)gravParameter[j]*sin;
			
			xVelocity[j] -= (long double)gravParameter[i]*cos;
			yVelocity[j] -= (long double)gravParameter[i]*sin;
		}
	}
}

void Bodies::move(void)
{
	for(int i=0; i<count; i++) 
	{
		xPosition[count] += xVelocity[count];
		yPosition[count] += yVelocity[count];
	}
}

void Bodies::create(int64_t xvel, int64_t yvel, int64_t xpos, int64_t ypos, int64_t gravP)
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
	*points = (SDL_Point *)malloc(sizeof(**points)*count);
	for(int i=0; i<count; i++)
	{
		(*points)[i].x = xPosition[count]/1000;
		(*points)[i].y = yPosition[count]/1000;
	}
	*cnt = count;
}
