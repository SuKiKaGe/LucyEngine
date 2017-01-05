#pragma once

#ifndef NEWGAMEMANAGER_H
#define NEWGAMEMANAGER_H

#include <string>

#include "Singleton.h"
#include "NewRenderManager.h"
#include "NewInputManager.h"

//#include "NewGameManager.cpp"

/**
Class NewGameManager
Implements this class code
*/
class NewGameManager : public Singleton <NewGameManager>
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	// Lets the constructor access to class Singleton
	friend class Singleton <NewGameManager>;

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

	void Start();
	void Stop();

	int mRunning;

	void Run();
	void Update();

	// Time manager
	void FPSChanged(int fps);

	void set_mRunning(int value);

	const float NewGameManager::UPDATE_INTERVAL = 1000.0f / 60.0f;

private:

	/**
	Constructor
	*/
	NewGameManager(void) //:mRunning(0), mWindow(NULL), mRenderer(NULL)
	{
		NewRenderManager::CreateSingleton();
		NewInputManager::CreateSingleton();
	}

	/**
	Destructor
	*/
	~NewGameManager(void)
	{
		Stop();
	}
};

#endif