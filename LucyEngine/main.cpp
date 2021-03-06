// LucyEngine

#include <SDL.h>
#include "GameManager.h"
#include "AudioManager.h"

int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	// game code eventually goes here
	// Comentario de prueba de Xhyon

	GameManager::CreateSingleton();

	AudioManager::GetInstance().loadMedia();
	AudioManager::GetInstance().playMedia();
	NewRenderManager::GetInstance().Draw();

	SDL_Delay(5000);

	//SDL_Quit();

	return 0;
}