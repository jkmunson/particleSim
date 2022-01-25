#include <main.h>
#include <renderer.h>
#include <config.h>

int main(int argc, char** argv) 
{
	Config config(argc, argv);
	printf("The config default resolution is %ix%i\n", config.video.windowWidth, config.video.windowHeight);
	printf("Hello World\n");
	rendererStart();
	return 1;
}
