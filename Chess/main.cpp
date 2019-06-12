#include "stdafx.h"
#include "SDL.h"
#undef main
#include <string>
#include <iostream>
#include "constants.h"
#include "LTexture.h"
#include "functions.h"
#include "globals.h"
#include "Chess_Frame.h"
#include "GameState.h"
using namespace std;

int main(int argc, char* args[]){
	if( !init() ){
		printf("Failed to initialized!\n");
	}else if( !loadMedia() ){
		printf("Failed to load media!\n");
	}else{
		SDL_Event e;
		currentState = new Intro();	
		
		Uint32 startTime = 0; //time counter	
		while( stateID != STATE_EXIT ){
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);	

			background.setAlpha(90); //blur background
			background.render(0, 0);
						
			currentState->handleEvent(e);
			currentState->update();
			change_state();
			currentState->render();
			
			SDL_RenderPresent(renderer);			
								
			Uint32 endTime = SDL_GetTicks();//Regulating FPS
			if( (endTime - startTime) < 1000.0/FRAMES_PER_SECOND){
				SDL_Delay( 1000.0/FRAMES_PER_SECOND - (double)(endTime - startTime) );//180FPS
			}
			startTime = SDL_GetTicks();
			
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					stateID = STATE_EXIT;
				}
			}				
		}
		delete currentState; currentState = NULL;
	}
	close();
	return 0;
}
