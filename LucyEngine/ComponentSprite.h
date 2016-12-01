#pragma once
#ifndef COMPONENTSPRITE_H
#define COMPONENTSPRITE_H

#include "Component.h"
#include <iostream>
using namespace std;

#define SPRITE_PATH "../"

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

/**
Class Component Sprite
Implements this class code
*/
class ComponentSprite : public Component
{
	/**********************************************************************************************************************/
	// ASSOCIATIONS
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	// CONSTANTS
	/**********************************************************************************************************************/
	
	//static const std::string SPRITE_PATH = "../";


	SDL_Surface * mSprite = NULL;

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
	ComponentSprite( std::string spriteName ) :
		Component()
	{
		mSprite = RenderManager::GetInstance().loadSurface(SPRITE_PATH+spriteName);
	}

	/**
	Destructor
	*/
	~ComponentSprite(void)
	{
		cout << "Happy Image Destroyed" << endl;
	}

	virtual void Initialize()
	{
	}
	virtual void update()
	{
	}
};
#endif