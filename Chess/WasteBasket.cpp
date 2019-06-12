#include "WasteBasket.h"

WasteBasket::WasteBasket(){
	for(int i = 0; i<2; i++)
		for(int j = 0; j<5; j++)
			container[i][j] = 0;
	
}

WasteBasket::~WasteBasket(){}

void WasteBasket::add_pawn(bool isWhite){
	if( isWhite ) container[0][0]++;
	else container[1][0]++;
}

void WasteBasket::add_bishop(bool isWhite){
	if( isWhite ) container[0][1]++;
	else container[1][1]++;
}

void WasteBasket::add_knight(bool isWhite){
	if( isWhite ) container[0][2]++;
	else container[1][2]++;
}

void WasteBasket::add_rook(bool isWhite){
	if( isWhite ) container[0][3]++;
	else container[1][3]++;
}

void WasteBasket::add_queen(bool isWhite){
	if( isWhite ) container[0][4]++;
	else container[1][4]++;
}

void WasteBasket::render(){
	for(int i = 0; i<5; i++){
		int x = Ox - size;
		int y = Oy + (64*8 - 32*5)/2 + 32*5 - 32*i;
		for(int j = 0; j<container[0][i]; j++){
			x -= 7;
			
			SDL_Rect face;
			face.w = size;
			face.h = size;
			face.x = (5 - i)*size;
			face.y = size;
			
			sprite_sheet_texture_2.render(x, y, &face);
		}
	}
	
	for(int i = 0; i<5; i++){
		int x = Ox + 64*8;
		int y = Oy + (64*8 - 32*5)/2 + 32*5 - 32*i;
		for(int j = 0; j<container[1][i]; j++){
			x += 7;
			
			SDL_Rect face;
			face.w = size;
			face.h = size;
			face.x = (5 - i)*size;
			face.y = 0;
			
			sprite_sheet_texture_2.render(x, y, &face);
		}
	}	
}
