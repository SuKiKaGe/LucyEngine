#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Singleton.h"
#include "RenderManager.h"
#include "AudioManager.h"

/**
Class GameManager
Implements this class code
*/
class GameManager : public Singleton <GameManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <GameManager>;

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
	GameManager(void)
	{
		SDL_Init(SDL_INIT_VIDEO);

		RenderManager::CreateSingleton();
		AudioManager::CreateSingleton();

		//Start up SDL and create window
		if (!init())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{
				//Main loop flag
				bool quit = false;

				//Event handler
				SDL_Event e;

				//Set default current surface
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

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
		}
	}

	/**
	Destructor
	*/
	~GameManager(void)
	{
	}

};
#endif