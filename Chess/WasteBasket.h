#ifndef WASTEBASKET_H
#define WASTEBASKET_H

#include "LTexture.h"
#include "globals.h"
#include "SDL.h" 

#include <iostream>
using namespace std;


class WasteBasket{
	private:
		int container[2][5];
		const int size = 32;
	public:
		WasteBasket();
		~WasteBasket();
		void add_pawn(bool isWhite);
		void add_bishop(bool isWhite);
		void add_knight(bool isWhite);
		void add_rook(bool isWhite);		
		void add_queen(bool isWhite);
		
		void render();		
};

#endif
