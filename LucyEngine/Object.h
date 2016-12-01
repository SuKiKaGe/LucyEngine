#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Singleton.h"
#include "Component.h"

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Struct for Position
struct Position {
	float positionX;
	float positionY;
};

// Struct for Scale
struct Scale {
	float scaleX;
	float scaleY;
};

// Transform Component
struct Transform {
	Position position;
	Scale scale;
};

// Rotation - Future Implementation

Component *componentes[];

/**
Class Object
Implements this class code
*/
class Object
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <Object>;

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
	Object(void)
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