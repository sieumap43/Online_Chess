#include "King.h"
#include <iostream>
#include "constants.h"
#include <cmath>
using namespace std;

King::King(bool is_white):Piece(is_white){
	if(is_white){
		face.x = 0;
		face.y = 64;
		x_index = 0;
		y_index = 15;
	}else{
		face.y = 0;
		face.x = 0;
		x_index = 1;
		y_index = 15;
	}
	piecevalue = 100;
}

King::~King(){
}

void King::print(){
	if(isWhite) cout<<"White King";
	else cout<<"Black King";
}

bool King::is_path_blocked(int a, int b, Square* board[8][8]){
	if(toX == a && toY == b) return true;
	if( abs(toX-a) <= 64 && abs(toY-b) <= 64) return false;
	int p, q;
	int I, J;
	if( isWhite ){
		if(first_move){
			if( (a - Ox)/64 == 2 && (b - Oy)/64 == 7){
				if( board[2][7]->piece_x_index != -1 ) return true;				
				if( board[3][7]->piece_x_index != -1 ) return true;
				if( board[1][7]->piece_x_index != -1 ) return true;
				left_castling = true;
				return false;
			}
			if(	(a - Ox)/64 == 6 && (b - Oy)/64 == 7){
				if( board[5][7]->piece_x_index != -1 ) return true;
				if( board[6][7]->piece_x_index != -1 ) return true;
				right_castling = true;
				return false;				
			}
		}
	}else{
		if(first_move){
			if( (a - Ox)/64 == 2 && (b - Oy)/64 == 0 ){
				if( board[2][0]->piece_x_index != -1 ) return true;				
				if( board[3][0]->piece_x_index != -1 ) return true;
				if( board[1][0]->piece_x_index != -1 ) return true;
				left_castling = true;
				return false;
			}
			if(	(a - Ox)/64 == 6 && (b - Oy)/64 == 0){
				if( board[5][0]->piece_x_index != -1 ) return true;
				if( board[6][0]->piece_x_index != -1 ) return true;
				right_castling = true;
				return false;				
			}
		}
	}
	return true;
}

void King::move_to(int a, int b, Square* board[8][8]){
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


bool King::try_move_to(int a, int b,int &I, int &J, Chess_Frame* all){
	if( isCaptured) return false;
	if(toX == a && toY == b){
		I = -4;
		return false;
	}
	
	left_castling = false;
	right_castling = false;	
	if( is_path_blocked(a, b, all->board) ){
		I = -3;
		return false;	
	}		
	int X = toX;
	int Y = toY;
	int m = (a - Ox)/64;
	int n = (b - Oy)/64;
	int p = (X - Ox)/64;
	int q = (Y - Oy)/64;
	bool simulate_success = true;	
	
	if( left_castling) {
		if( all->is_king_checked(isWhite) ) return false;	
		int attacker_x_index;	
		if( isWhite ){
			if( !all->army[0][12]->first_move ) return false;			
			attacker_x_index = 1;				
		}else{
			if( !all->army[1][12]->first_move ) return false;				
			attacker_x_index = 0;
		}				
		for(int i = 0; i<=15; i++){
			if( all->army[attacker_x_index][i]->isCaptured ) continue;
			X = toX - 64;
			if( !all->army[attacker_x_index][i]->is_path_blocked(X, Y, all->board) ){ 
				return false;
			}
			X = toX -128;
			if( !all->army[attacker_x_index][i]->is_path_blocked(X, Y, all->board) ){ 
				return false;
			}			
		}
		return true;
	}
	
	if( right_castling ){
		if( all->is_king_checked(isWhite) ) return false;
		int attacker_x_index;				
		if( isWhite ){
			if( !all->army[0][13]->first_move ) return false;			
			attacker_x_index = 1;
		}else{
			if( !all->army[1][13]->first_move ) return false;			
			attacker_x_index = 0;
		}
		for(int i = 0; i<=15; i++){
			if( all->army[attacker_x_index][i]->isCaptured ) continue;
			X = toX + 64;
			if( !all->army[attacker_x_index][i]->is_path_blocked(X, Y, all->board) ){
				return false;
			}
			X = toX + 128;
			if( !all->army[attacker_x_index][i]->is_path_blocked(X, Y, all->board) ){ 
				return false;
			}			
		}
		return true;
	}
	
	if( ( all->board[m][n]->piece_x_index != -1 ) && ( isWhite == all->board[m][n]->isWhite ) ){ //if the square is occupied by an allied piece
		I = -2;
		return false;
	}
	
	if( all->board[m][n]->piece_x_index == -1 ){	//the square is empty
		all->board[p][q]->clear();	 //clear former square
		
		setPos(a, b, all->board);			//simulate move to latter square
		if( all->is_king_checked(isWhite) ){
			simulate_success = false;
		}
		all->board[m][n]->clear();	//clear latter square
		setPos(X, Y, all->board);			//move back to former square	
	}else{	//the square is occupied by an enemy piece
		I = all->board[m][n]->piece_x_index;
		J = all->board[m][n]->piece_y_index;

		all->board[p][q]->clear();
		all->army[I][J]->isCaptured = true;
		setPos(a, b, all->board);
		if( all->is_king_checked(isWhite) ){
			simulate_success = false;
		}
		all->army[I][J]->isCaptured = false;
		all->army[I][J]->setPos(a, b, all->board);
		setPos(X, Y, all->board);
	}
	return simulate_success;
}

bool King::initiate_move_to(int a, int b, Chess_Frame* all){
	if( a < Ox || a > (64*8 + Ox) || b<Oy || b > (64*8 + Oy) ) return false; 
	a = a/64*64;
	b = b/64*64;	
	int m = (a - Ox)/64;	//convert to matrix of squares coordinates	
	int n = (b - Oy)/64;	//(m,n) is the destination square coordinates
	int p = (toX - Ox)/64;	//(p,q) is the current square coordinates
	int q = (toY - Oy)/64;
	int I = -1, J = -1;	
	if( !try_move_to(a, b, I, J, all) ){
		int C,D;
		if( all->player1_turn ){
			C = (all->army[0][15]->getX() - Ox)/64;
			D = (all->army[0][15]->getY() - Oy)/64;
		}else{
			C = (all->army[1][15]->getX() - Ox)/64;
			D = (all->army[1][15]->getY() - Oy)/64;
			cout << "black king" << endl;
		}
		switch(I){
			case -2:
				cout<<"Cannot capture allied piece."<<endl;
				all->board[m][n]->glow_red();
				break;
			case -3:
				all->board[m][n]->glow_red();
				cout<<"Another is piece blocking path or the move doesn't follow rules."<<endl;		
				break;	
			case -4:
				break;	
			default:
				cout<<"The King is still or will be checked."<<endl;
				all->board[C][D]->glow_red();
				break;	
		}
		return false;
	}
	
	if( left_castling ){
		move_to(a, b, all->board);
		if( isWhite ) all->army[0][12]->move_to(3*64 + Ox, 7*64 + Oy, all->board);
		else all->army[1][12]->move_to(3*64 + Ox, Oy, all->board);
		return true;
	}
	if( right_castling ){
		move_to(a, b, all->board);
		if( isWhite ) all->army[0][13]->move_to(5*64 + Ox, 7*64 + Oy, all->board);
		else all->army[1][13]->move_to(5*64 + Ox, Oy, all->board);
		return true;
	}
	
	if( I >= 0 ){ //if there is a piece in the square, announce a capture move and remove the piece
		print();
		cout<<" captured ";					
		all->army[I][J]->print();
		cout<<"."<<endl;
		all->army[I][J]->remove(all->basket);
		if( all->player1_turn ) all->black_piece_captured_num++;
		else all->white_piece_captured_num++;				
	}else if( I == -1){
		print();
		cout<<" moved to empty square."<<endl;
	}	
	
	move_to(a, b, all->board);							
	return true;					
}

bool King::try_all_moves(Chess_Frame* all){
	int X = toX;
	int Y = toY;
	int I = -1;
	int J = -1;
	for(int i = -1; i<= 1; i++)
		for(int j = -1; j<=1; j++){
			if(i == 0 && j == 0) continue;
			int a = X + i*64;
			int b = Y + j*64;
			if( a<Ox || a>(64*7 + Ox) || b<Oy || b>(64*7 + Oy) ) continue;
			if( try_move_to(a, b, I, J, all) ) return false;			
		}	
	return true;
}
