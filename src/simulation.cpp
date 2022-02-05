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
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{50,250,80,55}, 0, height, rendererRef.windowArea.w-2 , rendererRef.windowArea.h - height) );
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
				bodies.create(0,0,event.button.x*100000, event.button.y*100000, 50000000000);
			if(event.button.button == SDL_BUTTON_RIGHT)
				bodies.create(0,14000,event.button.x*100000, event.button.y*100000, 400000000);
		break;
		
		case SDL_MOUSEBUTTONUP:
			//if(event.button.button == SDL_BUTTON_LEFT)
				//bodies.create(0,0,event.button.x*100000, event.button.y*100000, 4);
			if(event.button.button == SDL_BUTTON_RIGHT)
				bodies.create(0,-14000,event.button.x*100000, event.button.y*100000, 40000);
				
		case SDL_MOUSEMOTION:
		
		break;
		
		case SDL_MOUSEWHEEL:
			int x,y;
			SDL_GetMouseState(&x, &y);
			bodies.create(0,event.wheel.y*18000,x*100000, y*100000, 5000);
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
			//printf("%i with %i\n",i, j);
			int64_t x = xPosition[i] - xPosition[j];
			int64_t y = yPosition[i] - yPosition[j];
			//printf("x %li y%li\n", x, y);
			
			__int128 rsquaretemp = x*x + y*y;
			if (rsquaretemp < 1000000 ) continue; //Will violate conservation of momentum. For now, use this... but ultimately we want collisions
			
			double r = sqrtl((long double)rsquaretemp);
			//printf("r %f\n",r);
			
			int64_t rsquare = (rsquaretemp/20000)+1000;
			float sin = y/r;
			float cos = x/r;
			//printf("sin: %f cos %f \n", sin,cos);
			
			
			if (rsquare < gravParameter[j]){
				xVelocity[i] -= (gravParameter[j]*cos)/rsquare;
				yVelocity[i] -= (gravParameter[j]*sin)/rsquare;
			} else {
			}
			
			if (rsquare < gravParameter[i]){
				xVelocity[j] += (gravParameter[i]*cos)/rsquare;
				yVelocity[j] += (gravParameter[i]*sin)/rsquare;
			} else {
			}
			
			//printf("xvel: %li  yvel: %li\n", xVelocity[i], yVelocity[i]);
			//getchar();
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
	*points = (SDL_Point *)malloc(sizeof(**points)*count*5);
	for(int i=0; i<count*5; i=i+5)
	{
		(*points)[i].x = xPosition[i/5]/100000;
		(*points)[i].y = yPosition[i/5]/100000;
		
		(*points)[i+1].x = (xPosition[i/5]/100000+1);
		(*points)[i+1].y = (yPosition[i/5]/100000);
		
		(*points)[i+2].x = (xPosition[i/5]/100000-1);
		(*points)[i+2].y = (yPosition[i/5]/100000);
		
		(*points)[i+3].x = (xPosition[i/5]/100000);
		(*points)[i+3].y = (yPosition[i/5]/100000+1);
		
		(*points)[i+4].x = (xPosition[i/5]/100000);
		(*points)[i+4].y = (yPosition[i/5]/100000-1);
	}
	
	*cnt = (count*5);
}
