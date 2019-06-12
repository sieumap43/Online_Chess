#include "SDL.h"
#include "SDL_image.h"
#include <string>

#include "constants.h"
#include "functions.h"
#include "globals.h"
#include "LTexture.h"

bool init(){
	bool success = true;
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ){		//initialized SDL
		printf("SDL cannot initialized! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}else{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1") ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		
		window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL){
			printf("Window could not be created! SDL_GetError: %s\n", SDL_GetError());
			success = false;
		}else{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL){
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}else{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;	//Initialize SDL_image
				if( !(IMG_Init(imgFlags) & imgFlags) ){
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				
				if( TTF_Init() == -1 ){			//Initialize SDL_ttf
					printf("SDL_ttf could not initialized! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia(){
	bool success = true;
	font = TTF_OpenFont("font/Gasalt-Black.ttf", 40);		//load font
	if( font == NULL ){
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	
	if( !sprite_sheet_texture.loadFromFile("image/sprite.png") ){
		printf("Cannot load sprite sheet!\n");
		success = false;
	}
	if( !sprite_sheet_texture_2.loadFromFile("image/sprite_2.png") ){
		printf("Cannot load sprite sheet!\n");
		success = false;
	}	
	if( !white_prom_menu.loadFromFile("image/white_promote4.png") ){
		printf("Cannot load white promotion menu!\n");
		success = false;
	}
	if( !black_prom_menu.loadFromFile("image/black_promote4.png") ){
		printf("Cannot load black promotion menu!\n");
		success = false;
	}
	if( !button_texture.loadFromFile("image/button.png") ){
		printf("Cannot load button texture!\n");
		success = false;
	}
	if( !background.loadFromFile("image/background.jpg") ){
		printf("Cannot load background!\n");
		success = false;
	}else{
		background.setBlendMode( SDL_BLENDMODE_BLEND );		
	}
	if( !back_button_texture.loadFromFile("image/back.png") ){
		printf("Failed to load back button texture!\n");
		success = false;
	}
	if( !title_texture.loadFromFile("image/title.png") ){
		printf("Failed to load title texture!\n");
		success = false;
	}
	if( !pvp_text.loadFromFile("image/pvp.png") ){
		printf("Failed to load pvp text!\n");
		success = false;
	}
	if( !pvc_text.loadFromFile("image/pvc.png") ){
		printf("Failed to load pvc text!\n");
		success = false;
	}
	if( !quit_text.loadFromFile("image/quit.png") ){
		printf("Failed to load quit text!\n");
		success = false;
	}
	for(int i = 0; i<6; i++){
		string white_won_link = "image/white_won/" + to_string(i) + ".gif";
		string black_won_link = "image/black_won/" + to_string(i) + ".gif";
		string draw_won_link = "image/draw/" + to_string(i) + ".gif";
		if( !white_won[i].loadFromFile(white_won_link) ){
			printf("Failed to load GIF!\n");
			success = false;
		}
		if( !black_won[i].loadFromFile(black_won_link) ){
			printf("Failed to load GIF!\n");
			success = false;
		}
		if( !draw[i].loadFromFile(draw_won_link) ){
			printf("Failed to load GIF!\n");
			success = false;
		}
	}
	return success;
}

void close(){
	background.free();
	button_texture.free();
	title_texture.free();
	pvp_text.free();
	quit_text.free();
			
	sprite_sheet_texture.free();
	sprite_sheet_texture_2.free();
	black_prom_menu.free();
	white_prom_menu.free();
	back_button_texture.free();
	for(int i = 0; i<6; i++){
		white_won[i].free();
		black_won[i].free();
		draw[i].free();
	}	
	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	TTF_CloseFont( font );	
	renderer = NULL;
	window = NULL;
	font = NULL;
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
