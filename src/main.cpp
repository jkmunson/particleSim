#include <main.h>


int main(int argc, char** argv) 
{
	
	Config config(argc, argv);
	Renderer renderer("ParticleSim", config);
	Context context(config, renderer, NULL);
	context.run();
	return 0;
}
