#include <string>

#include "NewGameManager.h"
#include "NewRenderManager.h"
#include "NewInputManager.h"

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
		NewRenderManager::GetInstance().Set_mHero_x(NewRenderManager::GetInstance().HERO_SPEED);
	}
	if (mKeys[SDLK_UP]) {
		NewRenderManager::GetInstance().Set_mHero_y(-NewRenderManager::GetInstance().HERO_SPEED);
	}
	if (mKeys[SDLK_DOWN]) {
		NewRenderManager::GetInstance().Set_mHero_y(NewRenderManager::GetInstance().HERO_SPEED);
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