// LucyEngine
#include "NewGameManager.h"

int main(int argc, char ** argv)
{
	NewGameManager::CreateSingleton();

	// OLD CODE WORKING BAD BUT WITH ANOTATIONS ABOUT HOW TO RUN A GAME IN A RIGHT WAY
	/*
	// game code eventually goes here
	// Comentario de prueba de Xhyon

	GameManager::CreateSingleton();

	AudioManager::GetInstance().loadMedia();
	AudioManager::GetInstance().playMedia();
	//for (int i = 0; i < 100000000; i++)
	{
		NewRenderManager::GetInstance().Draw();
	}
	

	SDL_Delay(5000);

	//SDL_Quit();



	//Start game
	{
		// Example of functionalities
		ObjectManager::GetInstance().AddObject( new Cat() )
			Cat cat = new Cat("cat.bmp", pos, orientation, sound);;
				{
					Update() {
						if (InputManager.Key()) {
							Cat.Position()

						}
					}
				}


		new Mouse()



		}


		{
			Object cat = new Object("cat.bmp", ...);

			mouse = new Object( mouse )
	

				if (InputManager.Key()) {
					Cat.Position()

				}

				if( Cat.Touches(mouse ))
					win()
			}
			
		}
	*/

	return 0;
}