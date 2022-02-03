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
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,250,250,255}, 0, height, rendererRef.windowArea.w-2 , rendererRef.windowArea.w - height) );
	
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
			exit(0);
		break;
		
		case SDL_MOUSEBUTTONDOWN:
			
		break;
		
		case SDL_MOUSEMOTION:
		
		break;
		
		default:
			//printf("Unhandeled Event %i\n", event.type);
		break;
		}
	}
	
	height += direction;
	if((height > (rendererRef.windowArea.h - 2)) || height < 0) direction = (-1)*direction;
	
}
