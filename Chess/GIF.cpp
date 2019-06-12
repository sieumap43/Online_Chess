#include "GIF.h"

GIF::GIF(bool is_white, bool is_draw){
	isWhite = is_white;	
	isDraw = is_draw;
	current_frame = 0;
	x = 0;
	y = 0;
	width = black_won[0].getWidth();
	height = black_won[0].getHeight();
}

GIF::~GIF(){
}

int GIF::getWidth(){
	return width;
}

int GIF::getHeight(){
	return height;
}

void GIF::setPos(int a, int b){
	x = a;
	y = b;
}

void GIF::update(){
	if( show ){
		if( current_frame == (frames_number*10 - 1) ) current_frame = 0;
		else current_frame++;		
	}
}

void GIF::render(){
	if( show ){
		if( isDraw ) draw[current_frame/10].render(x, y);
		else if( isWhite ) white_won[current_frame/10].render(x, y);
		else black_won[current_frame/10].render(x, y);		
	}
}

void GIF::show_gif(){
	show = true;
}
