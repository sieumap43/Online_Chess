#include "Rook.h"
#include "globals.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace std;

Rook::Rook(bool is_white, int number):Piece(is_white){
	if(is_white){
		face.x = 64*2;
		face.y = 64;
		x_index = 0; 
	}else{
		face.x = 64*2;
		face.y = 0;
		x_index = 1;
	}	
	y_index = number;
	piecevalue = 50;
}

Rook::~Rook(){
}

void Rook::print(){
	if(isWhite) cout<<"White Rook";
	else cout<<"Black Rook";
}

void Rook::remove(WasteBasket* basket){
	if( !isWhite ){
		isCaptured = true;
	}else{
		isCaptured = true;
	}	
	basket->add_rook(isWhite);
}

bool Rook::is_path_blocked(int a, int b, Square* board[8][8]){
	int n = (a - toX);	//the distance between the destination (a,b) and the current position (x,y)
	int m = (b - toY);
	int p, q;
	if(m == 0){			//rook moves horizontally
		n /= 64;
		m /= 64;
		for(int i = 1; i<abs(n); i++){	//traverse all the squares between the destination (a,b) and the current position (x,y)
			p = (toX - Ox)/64 + i*n/abs(n);
			q = (toY - Oy)/64;
			if( board[p][q]->piece_x_index != -1 ) return true;	//check_path IS blocked		
		}
		return false;	//check_path NOT blocked
	}
	else if(n == 0){	//rook moves vertically
		n /= 64;
		m /= 64;	
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64;
			q = (toY - Oy)/64 + i*m/abs(m);
			if( board[p][q]->piece_x_index != -1 ) return true;	//check_path IS blocked
		}
		return false;	//check_path NOT blocked
	}		
	return true;		//invalid check_path
}

void Rook::move_to(int a, int b, Square* board[8][8]){
	int m = (a - Ox)/64;	
	int n = (b - Oy)/64;	
	int p = (toX - Ox)/64;	
	int q = (toY - Oy)/64;
	
	toX = a;
	toY = b;
	if( first_move ) first_move = false;	
	just_moved_pawn_x = -1;
	just_moved_pawn_y = -1;
	board[m][n]->piece_x_index = x_index;
	board[m][n]->piece_y_index = y_index;
	board[m][n]->isWhite = isWhite;	
	board[p][q]->clear();
}

void Rook::mark_path_to(int a, int b, Chess_Frame* all){
	all->check_path->append( all->board[(toX - Ox)/64][(toY - Oy)/64] );	
	int n = a - toX;
	int m = b - toY;
	int p, q;
	if(m == 0){			//rook moves horizontally
		n /= 64;
		m /= 64;
		for(int i = 1; i<abs(n); i++){	//traverse all the squares between the destination (a,b) and the current position (x,y)
			p = (toX - Ox)/64 + i*n/abs(n);
			q = (toY - Oy)/64;
			all->check_path->append(all->board[p][q]);			
		}
	}else if(n == 0){
		n /= 64;
		m /= 64;	
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64;
			q = (toY - Oy)/64 + i*m/abs(m);
			all->check_path->append(all->board[p][q]);				
		}
	}
}

bool Rook::try_all_moves(Chess_Frame* all){
	if( isCaptured ) return true;
	int top_limit = Oy;
	int bot_limit = 64*7 + Oy;
	int left_limit = Ox;
	int right_limit = 64*7 + Ox;
	int X = toX;
	int Y = toY;
	int I = -1, J = -1;
	while(Y >= top_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;
		Y -= 64;	//move rook vertically upward
	}
	X = toX; Y = toY;	
	while( Y <= bot_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;	
		Y += 64;	//move rook downward
	}
	X = toX; Y = toY;	
	while( X >= left_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X -= 64;	//move rook to the left		
	}
	X = toX; Y = toY;
	while( X <= right_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X += 64;	//move rook to the right		
	}
	return true;					
}
