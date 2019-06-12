#include "SDL.h"
#include "Square.h"
#include "globals.h"
#include <iostream>
using namespace std;
Square::Square(){
	x = 0;
	y = 0;
	piece_x_index = -1;
	piece_y_index = -1;
	red = 0;
	green = 0;
}

Square::Square(const Square& b){
	red = b.red;
	green = b.green;
	x = b.x;
	y = b.y;
	piece_x_index = -1;
	piece_y_index = -1;
	isWhite = b.isWhite;
}

Square::~Square(){}

void Square::setPos(int a, int b){
	x = a;
	y = b;
}

void Square::clear(){
	piece_x_index = -1;
	piece_y_index = -1;
}

void Square::print(){
	cout<<x<<" "<<y<<"||"<<x/64<<" "<<y/64<<endl;
}


void Square::glow_red(){
	red = 60;
}

void Square::glow_green(){
	green = 60;
}

void Square::stop_glowing_green(){
	green = 0;
}

void Square::update(){
	if(red > 0){
		red--;
	}
}

void Square::render(){
	if(red > 0){
		SDL_Rect square = {x, y, 64, 64};
		SDL_SetRenderDrawColor(renderer, 222, 31, 0, 0xFF);
		SDL_RenderFillRect(renderer, &square);		
	}
	if(green > 0){
		SDL_Rect square = {x, y, 64, 64};
		SDL_SetRenderDrawColor(renderer, 0, 198, 87, 0xFF);
		SDL_RenderFillRect(renderer, &square);		
	}
}

//----------------------------------------------------------------//

Path::Path(){
	size = 0;
	checker_num = 0;
	for(int i = 0; i<2; i++)
		for(int j = 0; j<2; j++)
			checker[i][j] = -1;
	for(int i = 0; i<7; i++)
		array[i] = NULL;
}

Path::~Path(){
	for(int i = 0; i<7; i++)
		array[i] = NULL;
}

void Path::add_checker(int x, int y){
	checker_num++;
	if( checker_num > 2){
		cout<<"Error, more than 2 checkers\n"; //in chess there can only be maximum 2 checkers
		return;
	}
	checker[0][checker_num - 1] = x;
	checker[1][checker_num - 1] = y;
}

void Path::append(Square* sq){
	if(checker_num == 2) return;
	size++;
	array[size - 1] = sq;
}

void Path::print(){
	for(int i = 0; i<size; i++){
		array[i]->print();
	}
}

void Path::clear(){
	size = 0;
	checker_num = 0;
	for(int i = 0; i<2; i++)
		for(int j = 0; j<2; j++)
			checker[i][j] = -1;
	for(int i = 0; i<7; i++)
		array[i] = NULL;			
}

