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



	//Start game
	{

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
    

	return 0;
}