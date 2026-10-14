/*
    Getting started with SDL2 - Just project setup and includes.  
*/

//For exit()
#include <cstdlib>

// for cout etc. 
#include <iostream>

#ifndef _WIN32
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#else
#include "SDL.h"
#include "SDL_image.h"
#endif

int main( int argc, char* args[] )
{
	SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << "Hello World" << std::endl;

	exit(EXIT_SUCCESS);
}
