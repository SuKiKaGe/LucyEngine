#pragma once
#pragma once
#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "Singleton.h"

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::string str = IMG_GetError();
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

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
	
	//Current displayed image
	SDL_Surface* gCurrentSurface = NULL;

	/**********************************************************************************************************************/
	// METHODS
	/**********************************************************************************************************************/

public:

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
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				printf("Warning: Linear texture filtering not enabled!");
			}

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

				//Create vsynced renderer for window
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}
				}
			}
		}

		//return success;

		// Testing That Works - After that it will be refactored in another script
		//Start up SDL and create window

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

				//Current animation frame
				int frame = 0;

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
					}

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Render current frame
					SDL_Rect* currentClip = &gSpriteClips[frame / 4];
					gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

					//Update screen
					SDL_RenderPresent(gRenderer);

					//Go to next frame
					++frame;

					//Cycle animation
					if (frame / 4 >= WALKING_ANIMATION_FRAMES)
					{
						frame = 0;
					}
			}
		}
	}

	/**
	Destructor
	*/
	~RenderManager(void)
	{
		//Deallocate surface
		SDL_FreeSurface(gHelloWorld);
		gHelloWorld = NULL;

		//Free loaded images
		gSpriteSheetTexture.free();

		//Destroy window
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;

		gRenderer = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

	bool loadMedia()
	{
		//Loading success flag
		bool success = true;

		// First tutorial for just a background in the main screen
		/*
		//Load splash image
		gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
		if (gHelloWorld == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
			success = false;
		}
		*/

		//Load sprite sheet texture
		if (!gSpriteSheetTexture.loadFromFile("../cat.bmp"))
		{
			printf("Failed to load walking animation texture!\n");
			success = false;
		}
		else
		{
			//Set sprite clips
			gSpriteClips[0].x = 0;
			gSpriteClips[0].y = 0;
			gSpriteClips[0].w = 64;
			gSpriteClips[0].h = 205;

			gSpriteClips[1].x = 64;
			gSpriteClips[1].y = 0;
			gSpriteClips[1].w = 64;
			gSpriteClips[1].h = 205;

			gSpriteClips[2].x = 128;
			gSpriteClips[2].y = 0;
			gSpriteClips[2].w = 64;
			gSpriteClips[2].h = 205;

			gSpriteClips[3].x = 196;
			gSpriteClips[3].y = 0;
			gSpriteClips[3].w = 64;
			gSpriteClips[3].h = 205;
		}

		return success;
	}

	SDL_Surface* loadSurface(std::string path)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		return loadedSurface;
	}

	SDL_Surface* GetCurrentSurface(void) { return gCurrentSurface; }
	void SetCurrentSurface(SDL_Surface * sdl_Surface) { gCurrentSurface = sdl_Surface; }

};
#endif