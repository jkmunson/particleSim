#include <mainMenu.h>

MainMenu::MainMenu(Renderer &renderer) 
: Scene(renderer)
{
	SDL_Surface *temp = IMG_Load("data/img/splash.png");//HARDCODED
	if(!temp) IMG_ERROR_EXIT();
	splash = SDL_CreateTextureFromSurface(rendererRef.renderer, temp);
	if(!splash) SDL_ERROR_EXIT();
	SDL_FreeSurface(temp);
}

MainMenu::~MainMenu()
{
	SDL_DestroyTexture(splash);
}

void MainMenu::populateRenderingStack(std::stack<Sprite *> &renderingStack) 
{
	for(int i = 0; i<250000; i++) 
	renderingStack.push( new Nothing(SDL_BLENDMODE_NONE) );
	
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{100,250,50,255}, 0, height, rendererRef.windowArea.w-2 , height) );
	
	renderingStack.push( new Background( SDL_BLENDMODE_NONE, splash) );
	
}
void MainMenu::updateInternalState(void)
{
	//Nothing to do here, for main menu.
	height++;
	if(height > (rendererRef.windowArea.h - 2)) height=0;
}
