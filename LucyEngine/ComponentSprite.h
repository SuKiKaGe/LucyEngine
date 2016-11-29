#pragma once
#ifndef COMPONENTSPRITE_H
#define COMPONENTSPRITE_H

#include "Component.h"
#include <iostream>
using namespace std;

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
		cout << "Happy Image Loaded" << endl;
		ResourcesManager.loadSprite(spriteName);
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