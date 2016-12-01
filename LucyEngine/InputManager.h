#pragma once
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Singleton.h"
#include "RenderManager.h"

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

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

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

/**
Class RenderManager
Implements this class code
*/
class InputManager : public Singleton <InputManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <InputManager>;

	/**********************************************************************************************************************/
	// CONSTANTS
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	// TYPES
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	// METHODS
	/**********************************************************************************************************************/

public:

	/**
	Constructor
	*/
	InputManager(void)
	{
		//InputManager::CreateInstance();

		/*
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
		*/

		//return success;

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Set default current surface
		RenderManager::GetInstance().gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				//User presses a key
				else if (e.type == SDL_KEYDOWN)
				{
					//Select surfaces based on key press
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
						break;

					case SDLK_DOWN:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
						break;

					case SDLK_LEFT:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
						break;

					case SDLK_RIGHT:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
						break;

					default:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
						break;
					}
				}
			}

			//Apply the current image
			SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	/**
	Destructor
	*/
	~InputManager(void)
	{
		//Deallocate surfaces
		for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
		{
			SDL_FreeSurface(gKeyPressSurfaces[i]);
			gKeyPressSurfaces[i] = NULL;
		}

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

		//Load default surface
		gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = RenderManager::GetInstance().loadSurface("../press.bmp");
		if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
		{
			printf("Failed to load default image!\n");
			success = false;
		}

		//Load up surface
		gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = RenderManager::GetInstance().loadSurface("../up.bmp");
		if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
		{
			printf("Failed to load up image!\n");
			success = false;
		}

		//Load down surface
		gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = RenderManager::GetInstance().loadSurface("../down.bmp");
		if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
		{
			printf("Failed to load down image!\n");
			success = false;
		}

		//Load left surface
		gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = RenderManager::GetInstance().loadSurface("../left.bmp");
		if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
		{
			printf("Failed to load left image!\n");
			success = false;
		}

		//Load right surface
		gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = RenderManager::GetInstance().loadSurface("../right.bmp");
		if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
		{
			printf("Failed to load right image!\n");
			success = false;
		}

		return success;
	}
};
#endif