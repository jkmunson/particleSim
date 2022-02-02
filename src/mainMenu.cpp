#include <mainMenu.h>

MainMenu::MainMenu(Renderer &renderer) 
: Scene(renderer)
{
	SDL_Surface *temp = IMG_Load("data/img/splash.png");//HARDCODED
	if(!temp) IMG_ERROR_EXIT();
	splash = SDL_CreateTextureFromSurface(rendererRef.renderer, temp);
	if(!splash) SDL_ERROR_EXIT();
	SDL_FreeSurface(temp);
	simFrameDeltaMs = 5;
}

MainMenu::~MainMenu()
{
	SDL_DestroyTexture(splash);
}

void MainMenu::populateRenderingStack(std::stack<Sprite *> &renderingStack) 
{
	
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{100,250,blue,255}, 0, height, rendererRef.windowArea.w-2 , height) );
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,blue,blue,255}, 0, height+blue, rendererRef.windowArea.w-2 , height+1) );
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,blue,blue,255}, 0, height-255+blue, rendererRef.windowArea.w-2 , height-1) );
	
	renderingStack.push( new Background( SDL_BLENDMODE_NONE, splash) );
	
}
void MainMenu::updateInternalState(void)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		//printf("Event: %i\n",event.type);
		quit = (event.type == SDL_QUIT);
	}//placeholder
	
	//Nothing to do here, for main menu.
	height += direction;
	if((height > (rendererRef.windowArea.h - 2)) || height < 0) direction = (-1)*direction;
	blue = (height*255) / rendererRef.windowArea.h;
}
