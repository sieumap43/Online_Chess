#ifndef PROMOTION_MENU_H
#define PROMOTION_MENU_H

#include "SDL.h"
#include "LTexture.h"
#include "globals.h"
#include <string>
#include <iostream>
using namespace std;

class Promote_options
{
	public:
		Promote_options();
		~Promote_options();
		void setPos(int a, int b);
		void handleEvent(SDL_Event &e, int &piece_type);
		void render(bool is_white);
	protected:
		int x, y;
		int width, height;
		bool mouse_pressing = false;
		bool mouse_releasing = true;
		bool chosen = false;
};

#endif
