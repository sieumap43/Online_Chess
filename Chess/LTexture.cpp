#include "LTexture.h"

LTexture background;
LTexture title_texture;
LTexture button_texture;
LTexture pvp_text;
LTexture pvc_text;
LTexture lan_text;
LTexture join_game_text;
LTexture host_game_text;
LTexture quit_text;

LTexture sprite_sheet_texture;
LTexture sprite_sheet_texture_2;
LTexture black_prom_menu;
LTexture white_prom_menu;
LTexture back_button_texture;
LTexture white_won[6];
LTexture black_won[6];
LTexture draw[6];


LTexture::LTexture(){
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture(){
	free();
}

bool LTexture::loadFromFile(std::string check_path){
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(check_path.c_str());
	if(loadedSurface == NULL){
		printf("Failed to load image%s! SDL_image Error: %s\n", check_path.c_str(), IMG_GetError());
	}else{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL){
			printf("Unable to create texture from image %s! SDL_Error: %s\n", check_path.c_str(), SDL_GetError());
		}else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
	}
	mTexture = newTexture;
	return mTexture!=NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor){
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if( textSurface == NULL){
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}else{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if( mTexture == NULL ){
			printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
		}else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}


void LTexture::render(int x, int y, SDL_Rect* clip){
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	if(clip != NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;		
	}
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

void LTexture::free(){
	if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int LTexture::getWidth(){
	return mWidth;
}

int LTexture::getHeight(){
	return mHeight;
}

//-------------------------------------------------------------------//


