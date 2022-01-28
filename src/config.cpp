#include <config.h>

Config::Config(int argc, char **argv)
{	
	//Process the args first, so that -altconfig or -noconfig can be set before loading the config file.
	this->readArgs(argc, argv, false);
	//TODO read config file
	//Process args a second time, so that arguments take precedence.
	this->readArgs(argc, argv, true);
}

void Config::readArgs(int argc, char **argv, bool silent)
{
	for(int i=0; i<argc; i++) 
	{
		
		if(!strcmp(argv[i], "-noconfig")) 
		{
			this->noconfig = true;
			if(!silent) printf("Skipping config file loading - Using defaults. NO SETTING CHANGES WILL BE SAVED.\n");
		}
		
		if(!strcmp(argv[i], "-help") || !strcmp(argv[i], "help") || !strcmp(argv[i], "-?"))
		{
			printf("Valid Arguments: \n %s\n %s\n %s\n",
				"-help",
				"-noconfig | skips loading the configuration file",
				"-altconfig (path/to/config/file) | Loads and uses an alternate configuration file");
			exit(0);
		}
		
	//TODO: Process all arguments
	}
}
 Config::~Config()
 {
	 //STUB: Write back config file.
 }
