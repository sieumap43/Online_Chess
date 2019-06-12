#include "Queen.h"
#include "globals.h"
#include <iostream>
#include "constants.h"
#include <cmath>
using namespace std;

Queen::Queen(bool is_white,int number):Piece(is_white){
	if(is_white){
		face.x = 64;
		face.y = 64;
		x_index = 0;
	}else{
		face.x = 64;
		face.y = 0;
		x_index = 1;
	}
	y_index = number;
	piecevalue = 90;
}

Queen::~Queen(){
}

void Queen::remove(WasteBasket* basket){
	if( !isWhite ){
		isCaptured = true;
	}else{
		isCaptured = true;
	}	
	basket->add_queen(isWhite);
}

void Queen::print(){
	if(isWhite) cout<<"White Queen";
	else cout<<"Black Queen";
}

bool Queen::is_path_blocked(int a, int b, Square* board[8][8]){
	int n = a - toX;	//calculate how many squares there are between
	int m = b - toY;	//the destination (a,b) and the current position (x,y)
	int p, q;
	if(m == 0){			//queen moves horizontally
		n /= 64;
		m /= 64;
		for(int i = 1; i<abs(n); i++){	//traverse all the squares between the destination (a,b) and the current position (x,y)
			p = (toX - Ox)/64 + i*n/abs(n);
			q = (toY - Oy)/64;
			if( board[p][q]->piece_x_index != -1 ){
				return true;
			}	
		}
		return false;
	}
	else if(n == 0){			//queen moves vertically
		n /= 64;
		m /= 64;	
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64;
			q = (toY - Oy)/64 + i*m/abs(m);
			if( board[p][q]->piece_x_index != -1 ){
				return true;
			}
		}
		return false;
	}					//queen moves diagonally, abs(n) equals abs(m)
	else if( abs( abs( (float)n / m) - 1 ) < 0.01 ){
		n /= 64;
		m /= 64;	
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64 + i*n/abs(n);
			q = (toY - Oy)/64 + i*m/abs(m);
			if( board[p][q]->piece_x_index != -1 ) return true;
		}
		return false;	
	}
	return true; //path is blocked (or path is invalid)
}

void Queen::mark_path_to(int a, int b, Chess_Frame* all){
	all->check_path->append( all->board[(toX - Ox)/64][(toY - Oy)/64] );	
	int n = a - toX;
	int m = b - toY;
	int p, q;
	if(m == 0){		//queen moves horizontally
		m /= 64;
		n /= 64;
		for(int i = 1; i<abs(n); i++){
			p = (toX - Ox)/64 + i*n/abs(n);
			q = (toY - Oy)/64;			
			all->check_path->append(all->board[p][q]);
		}		
	}else if(n == 0){
		m /= 64;
		n /= 64;
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64;
			q = (toY - Oy)/64 + i*m/abs(m);
			all->check_path->append(all->board[p][q]);
		}
	}else if( abs( abs( (float)n / m) - 1 ) < 0.01 ){
		n /= 64;
		m /= 64;	
		for(int i = 1; i<abs(m); i++){
			p = (toX - Ox)/64 + i*n/abs(n);
			q = (toY - Oy)/64 + i*m/abs(m);
			all->check_path->append(all->board[p][q]);		
		}
	}
}

bool Queen::try_all_moves(Chess_Frame* all){
	if( isCaptured ) return true;
	int top_limit = 0 + Oy;
	int bot_limit = 64*7 + Oy;
	int left_limit = 0 + Ox;
	int right_limit = 64*7 + Ox;
	int X = toX;
	int Y = toY;
	int I = -1, J = -1;
	while(Y >= top_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		Y -= 64;	//move queen vertically upward
	}
	X = toX; Y = toY;
	while( Y >= top_limit && X < left_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X -= 64;	//move queen upward to the left
		Y -= 64;
	}	
	X = toX; Y = toY;
	while( Y >= top_limit && X <= right_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X += 64;	//move queen upward to the right
		Y -= 64;
	}	
	X = toX; Y = toY;
	while( Y <= bot_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		Y += 64;	//move queen downward
	}
	X = toX; Y = toY;
	while( Y <= bot_limit && X >= left_limit ){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X -= 64;	//move queen downward to the left
		Y += 64;
	}	
	X = toX; Y = toY;
	while( Y <= bot_limit && X <= right_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X += 64;	//move queen downward to the right
		Y += 64;
	}
	X = toX; Y = toY;
	while( X >= left_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X -= 64;	//move queen to the left
	}
	X = toX; Y = toY;
	while( X <= right_limit){
		if( try_move_to(X, Y, I, J, all) ) return false;		
		X += 64;	//move queen to the right
	}
	return true;
}
