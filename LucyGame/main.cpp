// LucyEngine
#include "GameManager.h"
#include "AudioManager.h"

int main(int argc, char ** argv)
{

	// game code eventually goes here
	// Comentario de prueba de Xhyon

	GameManager::CreateSingleton();

	AudioManager::GetInstance().loadMedia();
	AudioManager::GetInstance().playMedia();

	SDL_Delay(5000);

	//SDL_Quit();




	return 0;
}