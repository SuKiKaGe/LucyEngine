#pragma once
#pragma once
#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "Singleton.h"

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

/**
Class RenderManager
Implements this class code
*/
class RenderManager : public Singleton <RenderManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <RenderManager>;

	/**********************************************************************************************************************/
	// CONSTANTS
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	// TYPES
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	// METHODS
	/**********************************************************************************************************************/

private:

	/**
	Constructor
	*/
	RenderManager(void)
	{
		//RenderManager::CreateInstance();

		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}

		//return success;
	}

	/**
	Destructor
	*/
	~RenderManager(void)
	{
		//Deallocate surface
		SDL_FreeSurface(gHelloWorld);
		gHelloWorld = NULL;

		//Destroy window
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

	bool loadMedia()
	{
		//Loading success flag
		bool success = true;

		//Load splash image
		gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
		if (gHelloWorld == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
			success = false;
		}

		return success;
	}
};
#endif