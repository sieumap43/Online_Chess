#include "Knight.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace std;

Knight::Knight(bool is_white, int number):Piece(is_white){
	if(is_white){
		face.x = 3*64;
		face.y = 64;
		x_index = 0;
	}else{
		face.x = 3*64;
		face.y = 0;
		x_index = 1;
	}
	y_index = number;
	piecevalue = 30;
}

Knight::~Knight(){
}

void Knight::print(){
	if(isWhite) cout<<"White Knight";
	else cout<<"Black Knight";
}

void Knight::remove(WasteBasket* basket){
	if( !isWhite ){
		isCaptured = true;
	}else{
		isCaptured = true;
	}	
	basket->add_knight(isWhite);
}

bool Knight::is_path_blocked(int a, int b, Square* board[8][8]){
	int m = a - toX;
	int n = b - toY;
	if( abs(m) == 128 && abs(n) == 64) return false;
	if( abs(m) == 64 && abs(n) == 128) return false;
	return true;
}

void Knight::mark_path_to(int a, int b, Chess_Frame* all){
	all->check_path->append( all->board[(toX - Ox)/64][(toY - Oy)/64] );
}

bool Knight::try_all_moves(Chess_Frame* all){
	if( isCaptured ) return true;
	int X;
	int Y;
	int I = -1, J = -1;
	int z = 1, w = 2;
	for(int g = 0; g<2; g++){
		z *= -1;		
		for(int h = 0; h<2; h++){
			w *= -1;
			X = toX + z*64;
			Y = toY + w*64;
			if( X < Ox || X > (64*7 + Ox) || Y < Oy || Y > (64*7 + Oy) ) continue;
			if( try_move_to(X, Y, I, J, all) ) return false;
		}
	}
	
	z = 2; w = 1;
	for(int g = 0; g<2; g++){
		z *= -1;		
		for(int h = 0; h<2; h++){
			w *= -1;
			X = toX + z*64;
			Y = toY + w*64;
			if( X < Ox || X > (64*7 + Ox) || Y < Oy || Y > (64*7 + Oy) ) continue;
			if( try_move_to(X, Y, I, J, all) ) return false;
		}
	}
	return true;	
}
