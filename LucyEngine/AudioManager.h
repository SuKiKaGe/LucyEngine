#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "Singleton.h"

//Using SDL, SDL_image, SDL_ttf, SDL_mixer, standard IO, math, and strings
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

/**
Class AudioManager
Implements this class code
*/
class AudioManager : public Singleton <AudioManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <AudioManager>;

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
	AudioManager(void)
	{
		//AudioManager::CreateInstance();

		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize SDL_mixer
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
		}

		//return success;
	}

	/**
	Destructor
	*/
	~AudioManager(void)
	{
		//Free the sound effects
		Mix_FreeChunk(gScratch);
		Mix_FreeChunk(gHigh);
		Mix_FreeChunk(gMedium);
		Mix_FreeChunk(gLow);
		gScratch = NULL;
		gHigh = NULL;
		gMedium = NULL;
		gLow = NULL;

		//Free the music
		Mix_FreeMusic(gMusic);
		gMusic = NULL;

		//Quit SDL subsystems
		Mix_Quit();
		//IMG_Quit();
		SDL_Quit();
	}

	bool loadMedia()
	{
		//Loading success flag
		bool success = true;

		//Load music
		gMusic = Mix_LoadMUS("21_sound_effects_and_music/beat.wav");
		if (gMusic == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		//Load sound effects
		gScratch = Mix_LoadWAV("21_sound_effects_and_music/scratch.wav");
		if (gScratch == NULL)
		{
			printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		gHigh = Mix_LoadWAV("../scratch.wav");
		if (gHigh == NULL)
		{
			printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		gMedium = Mix_LoadWAV("21_sound_effects_and_music/medium.wav");
		if (gMedium == NULL)
		{
			printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		gLow = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
		if (gLow == NULL)
		{
			printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		return success;
	}

	void playMedia()
	{
		Mix_PlayChannel(-1, gHigh, 0);

	}
};
#endif