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
	if(bodies.count>1) {
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
			bodies.create(0,0,event.button.x*1000, event.button.y*1000, 5);
		break;
		
		case SDL_MOUSEMOTION:
		
		break;
		
		default:
			//printf("Unhandeled Event %i\n", event.type);
		break;
		}
	}
	if(bodies.count>2) {
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
			printf("%i with %i\n",i, j);
			int64_t x = xPosition[i] - xPosition[j];
			int64_t y = yPosition[i] - yPosition[j];
			printf("x %li y%li\n", x, y);
			
			int64_t rsquare = x*x + y*y;
			printf("rsquare: %li\n", rsquare);
			double r = std::sqrt((double)rsquare);
			printf("r %f\n",r);
			
			float sin = y/r;
			float cos = x/r;
			printf("sin: %f cos %f \n", sin,cos);
			
			xVelocity[i] -= (long double)gravParameter[j]*cos;
			yVelocity[i] -= (long double)gravParameter[j]*sin;
			
			xVelocity[j] += (long double)gravParameter[i]*cos;
			yVelocity[j] += (long double)gravParameter[i]*sin;
			
			printf("xvel: %li  yvel: %li\n", xVelocity[i], yVelocity[i]);
			//getchar();
		}
	}
}

void Bodies::move(void)
{
	for(int i=0; i<count; i++) 
	{
		if(xPosition[i] > 2000000 || xPosition[i] < -1000000) count=0;
		xPosition[i] += xVelocity[i];
		yPosition[i] += yVelocity[i];
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
		(*points)[i].x = xPosition[i]/1000;
		(*points)[i].y = yPosition[i]/1000;
	}
	*cnt = count;
}
