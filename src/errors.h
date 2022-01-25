#pragma once
#include <errno.h>
#include <stdio.h>

#define SDL_ERROR_EXIT()	{ printf("SDL_Error: %s\n", SDL_GetError()	);	exit(1); }
#define IMG_ERROR_EXIT()	{ printf("IMG_Error: %s\n", IMG_GetError()	);	exit(1); }
#define SYS_ERROR_EXIT()	{ perror("System Error: " 					);	exit(1); }
#define ERROR_EXIT(err)		{ printf("Error: %s\n", err 				);	exit(1); }
