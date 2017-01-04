#pragma once

#ifndef NEWRENDERMANAGER_H
#define NEWRENDERMANAGER_H

#include "Singleton.h"
#include "NewGameManager.h"
#include "NewInputManager.h"

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <cstdio>  
#include <map>  
#include <string>

class Sprite {

public:

	int x;
	int y;
	Sprite() : x(0), y(0) { }

};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

/**
Class NewRenderManager
Implements this class code
*/
class NewRenderManager : public Singleton <NewRenderManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <NewRenderManager>;

	/**********************************************************************************************************************/
	// CONSTANTS
	/**********************************************************************************************************************/

	// Constants
	static const int          DISPLAY_WIDTH = 480;
	static const int          DISPLAY_HEIGHT = 320;
	

	static const float        UPDATE_INTERVAL;

	//static const std::string  MEDIA_PATH;

	/**********************************************************************************************************************/
	// TYPES
	/**********************************************************************************************************************/

	SDL_Window         *mWindow;
	SDL_Renderer       *mRenderer;

	SDL_Surface        *mScreenSurface = NULL;   // The surface contained by the window
	SDL_Surface        *mScratchSurface = NULL;   // Surface to use
	SDL_Texture        *mScratchTexture = NULL;   // Texture to use

	/**********************************************************************************************************************/
	// METHODS
	/**********************************************************************************************************************/

public:

	const std::string   NewRenderManager::MEDIA_PATH = "../Media/";

	static const int          HERO_SPEED = 2;

	Sprite              mHero;

	// Render manager
	void Draw();
	void FillRect(SDL_Rect* rc, int r, int g, int b);

	void Set_mHero_x(int value);
	void Set_mHero_y(int value);
	SDL_Renderer get_mWindow();
	/**
	Constructor
	*/
	NewRenderManager(void):(mWindow(NULL), mRenderer(NULL)
	{
		int flags = SDL_WINDOW_SHOWN;
		if (SDL_Init(SDL_INIT_EVERYTHING)) {
			return;
		}

		if (SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, flags, &mWindow, &mRenderer)) {
			return;
		}

		// Screen surface
		mScreenSurface = SDL_GetWindowSurface(mWindow);
		if (mScreenSurface == NULL) {
			return;
		}

		// Load BMP
		mScratchSurface = SDL_LoadBMP((NewRenderManager::MEDIA_PATH + "Scratch.bmp").c_str());
		if (mScratchSurface == NULL)
		{
			return;
		}

		mScratchTexture = SDL_CreateTextureFromSurface(mRenderer, mScratchSurface);
		if (mScratchTexture == NULL) {
			return;
		}
	}

	/**
	Destructor
	*/
	~NewRenderManager(void)
	{
		if (NULL != mRenderer) {
			SDL_DestroyRenderer(mRenderer);
			mRenderer = NULL;
		}
		if (NULL != mWindow) {
			SDL_DestroyWindow(mWindow);
			mWindow = NULL;
		}
	}
};

void NewRenderManager::Draw()
{
	// RENDER USING RENDERER

	// Clear screen  
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(mRenderer);

	//// Render hero  
	SDL_Rect heroRect;
	heroRect.x = mHero.x;
	heroRect.y = mHero.y;
	heroRect.w = 20;
	heroRect.h = 20;
	FillRect(&heroRect, 255, 0, 0);

	// Render Scratch
	SDL_Rect scracthRect;
	scracthRect.x = mHero.x + 100;
	scracthRect.y = mHero.y + 100;
	scracthRect.w = 75; // Scale
	scracthRect.h = 75; // Scale
	SDL_RenderCopy(mRenderer, mScratchTexture, NULL, &scracthRect);

	SDL_Rect scracthRect2;
	scracthRect2.x = mHero.x + 200;
	scracthRect2.y = mHero.y + 200;
	scracthRect2.w = 75; // Scale
	scracthRect2.h = 75; // Scale  
	SDL_RenderCopy(mRenderer, mScratchTexture, NULL, &scracthRect2);

	SDL_RenderPresent(mRenderer);
}

void NewRenderManager::FillRect(SDL_Rect* rc, int r, int g, int b)
{
	SDL_SetRenderDrawColor(mRenderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(mRenderer, rc);
}

SDL_Renderer get_mWindow() { return mWindow; };

void NewRenderManager::Set_mHero_x(int value) { mHero.x + value; };

void NewRenderManager::Set_mHero_y(int value) { mHero.y + value; };

#endif