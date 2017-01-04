#pragma once

#ifndef NEWINPUTMANAGER_H
#define NEWINPUTMANAGER_H

#include "Singleton.h"
#include "NewRenderManager.h"
#include "NewGameManager.h"

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
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

// Input manager
void NewInputManager::EventManagement()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			OnQuit();
			break;
		case SDL_KEYDOWN:
			OnKeyDown(&event);
			break;
		case SDL_KEYUP:
			OnKeyUp(&event);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
			break;
		}
	}
}

void NewInputManager::Update()
{
	if (mKeys[SDLK_LEFT]) {
		NewRenderManager::GetInstance().Set_mHero_x(-NewRenderManager::GetInstance().HERO_SPEED);
	}
	if (mKeys[SDLK_RIGHT]) {
		NewRenderManager::GetInstance().mHero.x += NewRenderManager::GetInstance().HERO_SPEED;
	}
	if (mKeys[SDLK_UP]) {
		NewRenderManager::GetInstance().mHero.y -= NewRenderManager::GetInstance().HERO_SPEED;
	}
	if (mKeys[SDLK_DOWN]) {
		NewRenderManager::GetInstance().mHero.y += NewRenderManager::GetInstance().HERO_SPEED;
	}
}

// Input Manager
void NewInputManager::OnKeyDown(SDL_Event* evt)
{
	mKeys[evt->key.keysym.sym] = 1;
}
void NewInputManager::OnKeyUp(SDL_Event* evt)
{
	mKeys[evt->key.keysym.sym] = 0;
}

// Event or input
void NewInputManager::OnQuit()
{
	NewGameManager::GetInstance().set_mRunning(0);
}

#endif