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
	//for(int i = 0; i<500000; i++) 
	//renderingStack.push( new Nothing(SDL_BLENDMODE_NONE) );
	
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{100,250,blue,255}, 0, height, rendererRef.windowArea.w-2 , height) );
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,blue,blue,255}, 0, height+blue, rendererRef.windowArea.w-2 , height+1) );
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,blue,blue,255}, 0, height-255+blue, rendererRef.windowArea.w-2 , height-1) );
	
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{100,250,blue,255}, height, 0, height , rendererRef.windowArea.h-2) );
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,blue,blue,255}, height, 0+blue, rendererRef.windowArea.h-2 , rendererRef.windowArea.h-2) );
	renderingStack.push( new Line(SDL_BLENDMODE_BLEND, Color{250,blue,blue,255}, height, 0-255+blue, rendererRef.windowArea.h-2 , rendererRef.windowArea.h-2) );
	
	renderingStack.push( new Background( SDL_BLENDMODE_NONE, splash) );
	
}
void MainMenu::updateInternalState(void)
{
	//Nothing to do here, for main menu.
	height += direction;
	if((height > (rendererRef.windowArea.h - 2)) || height < 0) direction = (-1)*direction;
	blue = (height*255) / rendererRef.windowArea.h;
	//std::cout << "Color: " << (int)blue << "\n" << std::flush;
	if(direction > 10 || direction < -10) direction = direction/5;
}
