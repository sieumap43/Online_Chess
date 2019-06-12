#ifndef GIF_H
#define GIF_H

#include "LTexture.h"
#include "globals.h"
#include "constants.h"

class GIF{	//show gif
	private:
		const int frames_number = 6;
		int current_frame;
		int x, y;
		int width, height;
		bool isWhite, isDraw;
		bool show = false;		
	public:
		GIF(bool is_white, bool is_draw = false);
		~GIF();
		int getWidth();
		int getHeight();
		void setPos(int X, int Y);
		void update();
		void render();
		void show_gif();
};

#endif
