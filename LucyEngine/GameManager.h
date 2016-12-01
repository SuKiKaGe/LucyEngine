#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Singleton.h"
#include "RenderManager.h"
#include "AudioManager.h"
#include "InputManager.h"

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
		InputManager::CreateSingleton();
	}

	/**
	Destructor
	*/
	~GameManager(void)
	{
	}

};
#endif