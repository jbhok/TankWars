#if defined (__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>

#include "tank.h"

using namespace std;

#if defined(__APPLE__)
//string var to hold the current working directory on _APPLE_
string currentWorkingDirectory (getcwd(NULL,0));

//create a string to link to the images folder on _APPLE_
string images_dir = currentWorkingDirectory + "/src/";

//week 5
//create a string to link to the audio folder on _APPLE_
string audio_dir = currentWorkingDirectory + "/src/";
#endif

//deltaTime car initialization - for frame rate independence
float deltaTime = 0.0;
float thisTime =0;
float lastTime= 0;

//main start
int main(){

	// *****CREAT ETHE SDL WINDOW - START &&&&&&
	//start SDL2
	SDL_Init(SDL_INIT_EVERYTHING);


	//create a SDL Window reference - pointer
	SDL_Window *window = nullptr;

	//create a SDL renderTarget - pointer
	SDL_Renderer *renderer = nullptr;

	//create a SDL Window in the middle of the screen
	window = SDL_CreateWindow("Tank Wars!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);





	//create an SDL RenderTaret
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// *********CREATE THE SDL WINDOW - END **********

	// *********caraubke creatuib - start**********
	//main loop flag
	bool quit =false;

	//event handler
	SDL_Event e;
	//*************baraibel creation - end**********

	//***Turn on Game controller Eventws *****
	SDL_GameControllerEventState(SDL_ENABLE);

	//****set up a Game Controller vaiable for player 1 *****
	SDL_GameController* gGameController0 = NULL;

	// ***Open Game Controller for player 1 ****
	gGameController0 = SDL_GameControllerOpen(0);

	//cREATE PLAYERS START*******************************************
	Tank tank1 = Tank(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 0.0,0.0);


	// MAIN GAME LOOP START ************

	while(!quit)
	{
		//create deltaTime - for grame reate independence
		thisTime= SDL_GetTicks();
		deltaTime=(float)(thisTime-lastTime)/1000;
		lastTime=thisTime;

		//handle events on queue -Keypresses and such START ********
		while(SDL_PollEvent(&e)!= 0)
		{
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit=true;
			}

			switch (e.type){

			case SDL_CONTROLLERBUTTONDOWN:

			if(e.cdevice.which == 0){

				if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A){

					break;
				}

			}

			break;

			case SDL_CONTROLLERAXISMOTION:
			tank1.OnControllerAxis(e.caxis);
			break;

			}




		}//POLL EVENT

		//update player 1 tank
		tank1.Update(deltaTime);

		//draw selections
		//claer the SDL RenderTarget
		SDL_RenderClear(renderer);

		tank1.Draw(renderer);

		SDL_RenderPresent(renderer);

	}
	//close and destroy the window
	SDL_DestroyWindow(window);

	//clean up
	SDL_Quit();

	return 0;
}
