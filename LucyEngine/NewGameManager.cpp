#include <string>

#include "NewGameManager.h"
#include "NewInputManager.h"
#include "NewRenderManager.h"

void NewGameManager::Start()
{
	mRunning = 1;
	Run();
}

void NewGameManager::Stop()
{
	SDL_Quit();
}

void NewGameManager::FPSChanged(int fps)
{
	//sprintf(szFps, "%s: %d FPS", "SDL2 Base C++ - Use Arrow Keys to Move", fps);
	std::string title = std::string("Test - FPS = ") + std::to_string(fps);

	SDL_SetWindowTitle(NewRenderManager::GetInstance().get_mWindow, title.c_str());
}

void NewGameManager::Run()
{
	// Time manager
	int past = SDL_GetTicks();
	int now = past;
	int pastFps = past;
	int fps = 0;

	while (mRunning) {
		int timeElapsed = 0;

		// Input Manager
		NewInputManager::GetInstance().EventManagement();

		// update/draw  
		now = SDL_GetTicks();
		timeElapsed = now - past;
		if (timeElapsed >= NewGameManager::GetInstance().UPDATE_INTERVAL) {
			past = now;

			NewGameManager::GetInstance().Update();
			NewRenderManager::GetInstance().Draw();

			++fps;
		}

		// fps  
		if (now - pastFps >= 1000) {
			pastFps = now;
			NewGameManager::GetInstance().FPSChanged(fps);
			fps = 0;
		}
	}
}

void NewGameManager::Update()
{
	NewInputManager::GetInstance().Update();
}

void NewGameManager::set_mRunning(int value) { mRunning = value; };