#pragma once

#ifndef NEWINPUTMANAGER_H
#define NEWINPUTMANAGER_H

#include "Singleton.h"
#include "NewRenderManager.h"
#include "NewGameManager.h"

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <cstdio>  
#include <string>
#include <map>  

/**
Class NewInputManager
Implements this class code
*/
class NewInputManager : public Singleton <NewInputManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <NewInputManager>;

	/**********************************************************************************************************************/
	// CONSTANTS
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	// TYPES
	/**********************************************************************************************************************/

	std::map<int, int>  mKeys; // No SDLK_LAST. SDL2 migration guide suggests std::map  

	/**********************************************************************************************************************/
	// METHODS
	/**********************************************************************************************************************/

public:

	// Input Manager
	void EventManagement();
	void Update();
	void OnQuit();
	void OnKeyDown(SDL_Event* event);
	void OnKeyUp(SDL_Event* event);

	/**
	Constructor
	*/
	NewInputManager(void)
	{
	}

	/**
	Destructor
	*/
	~NewInputManager(void)
	{
	}
};

#endif