#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
#include "globals.h"
#include "constants.h"

class LTexture{		//an object that holds images
	public:
		LTexture();
		~LTexture();
		bool loadFromFile(std::string check_path);	//load image
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		void render(int x, int y, SDL_Rect* clip = NULL);
		void free();	//free memory
		void setBlendMode(SDL_BlendMode blending);	//fade or unfade image
		void setAlpha(Uint8 alpha);
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* mTexture;
		int mWidth, mHeight;
};

/***** ALL THE IMAGES USED BY THE GAME *****/

extern LTexture background;
extern LTexture title_texture;
extern LTexture button_texture;
extern LTexture pvp_text;
extern LTexture pvc_text;
extern LTexture lan_text;
extern LTexture join_game_text;
extern LTexture host_game_text;
extern LTexture quit_text;

extern LTexture sprite_sheet_texture;
extern LTexture sprite_sheet_texture_2;
extern LTexture black_prom_menu;
extern LTexture white_prom_menu;
extern LTexture back_button_texture;
extern LTexture black_won[6];
extern LTexture white_won[6];
extern LTexture draw[6];

/********************************************/
#endif
