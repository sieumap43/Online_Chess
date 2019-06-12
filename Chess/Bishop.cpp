#include "Bishop.h"
#include "globals.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace std;

Bishop::Bishop(bool is_white, int number):Piece(is_white){
	if(is_white){
		face.x = 4*64;
		face.y = 64;
		x_index = 0;
	}else{
		face.x = 4*64;
		face.y = 0;
		x_index = 1;
	}
	y_index = number;
	piecevalue = 30;
}

Bishop::~Bishop(){
}

void Bishop::print(){
	if(isWhite) cout<<"White Bishop";
	else cout<<"Black Bishop";
}

void Bishop::remove(WasteBasket* basket){
	if( !isWhite ){
		isCaptured = true;
	}else{
		isCaptured = true;
	}
	basket->add_bishop(isWhite);
}

bool Bishop::is_path_blocked(int a, int b, Square* board[8][8]){
	int m = a - toX;
	int n = b - toY;
	int p, q;
	if( abs( abs( (float)m / n) - 1 ) < 0.01 ){
		n /= 64;
		m /= 64;	
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64 + i*m/abs(m);
			q = (toY - Oy)/64 + i*n/abs(n);
			if( board[p][q]->piece_x_index != -1 ){
				return true;
			}
		}
		return false;	
	}
	return true;	
}

void Bishop::mark_path_to(int a, int b, Chess_Frame* all){
	all->check_path->append( all->board[(toX - Ox)/64][(toY - Oy)/64] ); //add the square the piece is sitting in go the check_path array	
	int m = a - toX;
	int n = b - toY;
	int p, q;
	if( abs( abs( (float)m / n) - 1 ) < 0.01 ){
		m /= 64;
		n /= 64;	
		for(int i = 1; i<abs(n); i++){
			p = (toX - Ox)/64 + i*m/abs(m);
			q = (toY - Oy)/64 + i*n/abs(n);
			all->check_path->append(all->board[p][q]);	//add square between the piece and the destination	
		}
	}		
}

bool Bishop::try_all_moves(Chess_Frame* all){
	if( isCaptured ) return true;
	int top_limit = Oy;
	int bot_limit = 64*7 + Oy;
	int left_limit = Ox;
	int right_limit = 64*7 + Ox;
	int X = toX;
	int Y = toY;
	int I = -1, J = -1;
	while( Y >= top_limit && X < left_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X -= 64;	//move bishop upward to the left
		Y -= 64;
	}	
	X = toX; Y = toY;
	while( Y >= top_limit && X <= right_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X += 64;	//move bishop upward to the right
		Y -= 64;
	}	
	X = toX; Y = toY;	
	while( Y <= bot_limit && X >= left_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X -= 64;	//move bishop downward to the left
		Y += 64;
	}	
	X = toX; Y = toY;
	while( Y <= bot_limit && X <= right_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X += 64;	//move bishop downward to the right
		Y += 64;
	}
	return true;
}
