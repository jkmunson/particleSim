#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*! Configuration Singleton, used to read/write the configuration file and 
 * read in arguments that are used in the initialization of other objects. */

class Config
{
	public:
	struct Video
	{
		//see https://wiki.libsdl.org/SDL_WindowFlags
		//!No flag = windowed. Could also be SDL_WINDOW_BORDERLESS, SDL_WINDOW_FULLSCREEN etc. Should | in SDL_WINDOW_INPUT_GRABBED for fullscreen.
		uint32_t windowType = 0;
		uint32_t windowWidth = 1200;
		uint32_t windowHeight = 675;
	};
	Video video;
	
	bool silent = false;
	
	//FIXME: Use default constructor, implement a config loading method. NOTHING GUARENTEED TO BE INITIALIZED CURRENTLY
	explicit Config(int argc, char **argv);
	~Config();
	void readArgs(int argc, char **argv, bool silent);
	
	private:
	//! When set, skip loading config file.
	bool noconfig = false;
	const char *configPath = "data/config";
};
