#include "Promote_options.h"

Promote_options::Promote_options(){
	width = black_prom_menu.getWidth();
	height = black_prom_menu.getHeight();
	x = 0;
	y = 0;
}

Promote_options::~Promote_options(){}

void Promote_options::setPos(int a, int b){
	x = a;
	y = b;
}

void Promote_options::handleEvent(SDL_Event &e, int &piece_type){
	if( e.type == SDL_MOUSEBUTTONDOWN && !mouse_pressing){
		int a,b;
		int w = width/4;	//divide the image into 4 subimages showing 4 options
		int h = height;		
		SDL_GetMouseState(&a, &b);
		
		for(int i = 0; i<4; i++){	//determine which options the mouse clicked on
			if( a >= (x + i*w) && a < (x + (i + 1)*w) && b >= y && b <= (y + h) ){
				mouse_pressing = true;
				mouse_releasing = false;
				chosen = true;
				piece_type = i + 1;				
				break;			
			}
		}			
	}else if( e.type == SDL_MOUSEBUTTONUP && !mouse_releasing){
		mouse_pressing = false;
		mouse_releasing = true;
	}else if( e.type == SDL_MOUSEMOTION){
		int a, b;
		int w = width/4;
		int h = height;
		SDL_GetMouseState(&a, &b);
		for(int i = 0; i<4; i++){	//determine which options the mouse is hovering over
			if( a >= (x + i*w) && a < (x + (i + 1)*w) && b >= y && b <= (y + h) ){
				SDL_Rect square = {x + i*w, y, w, h};
				SDL_SetRenderDrawColor(renderer, 0, 198, 87, 0xFF);
				SDL_RenderFillRect(renderer, &square);	
				break;			
			}
		}
	}
	
}

void Promote_options::render(bool is_white){
	if( !is_white ) white_prom_menu.render(x, y);	//if promote white pawn, show white promotion options
	else black_prom_menu.render(x, y);					//else show black promotion options
}


