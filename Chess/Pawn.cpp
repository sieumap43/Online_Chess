#include "Pawn.h"
#include "globals.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace std;

Pawn::Pawn(bool is_white, int number):Piece(is_white){
	if(is_white){
		face.x = 64*5;
		face.y = 64;
		x_index = 0;
		
	}else{
		face.x = 64*5;
		face.y = 0;
		x_index = 1;
	}
	y_index = number;
	piecevalue = 10;
}

Pawn::~Pawn(){
}

void Pawn::print(){
	if(isWhite) cout<<"White Pawn";
	else cout<<"Black Pawn";
}

bool Pawn::initiate_move_to(int a, int b, Chess_Frame* all){
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
	
	if( en_passant ){
		cout<<"En passant."<<endl;
		I = just_moved_pawn_x;
		J = just_moved_pawn_y;		
		int g = (all->army[I][J]->getX() - Ox)/64;
		int h = (all->army[I][J]->getY() - Oy)/64;
		
		if( all->player1_turn ) all->black_piece_captured_num++;
		else all->white_piece_captured_num++;		
				
		all->army[I][J]->remove(all->basket);
		all->board[g][h]->clear();		
		move_to(a, b, all->board);
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

bool Pawn::pawn_is_path_blocked(int a, int b, Square* board[8][8]){
	int m = a - toX;
	int n = b - toY;
	int p, q;
	if( isWhite ){
		if( m == 0 && n == -64 ){
			p = (toX - Ox)/64;
			q = (toY - Oy)/64 - 1;
			if( board[p][q]->piece_x_index != -1 ) return true;
			return false;				
		}		
		if( first_move ){
			if(	m == 0 && n == -128 ){
				p = (toX - Ox)/64;
				q = (toY - Oy)/64 - 1;
				if( board[p][q]->piece_x_index != -1 ) return true;

				q = (toY - Oy)/64 - 2;
				if( board[p][q]->piece_x_index != -1 ) return true;				
				return false;				
			}
		}
		if( abs(m) == 64 && n == -64){
			int g = (toX - Ox)/64 + abs(m)/m;			
			int h = (toY - Oy)/64;
			if( just_moved_pawn_x != -1){
				if( h == 3 && g >= 0 && g <= 7){
					if( board[g][h]->piece_x_index == just_moved_pawn_x 
					 && board[g][h]->piece_y_index == just_moved_pawn_y ){
					 	en_passant = true;
						return false;	
					}
				}
			}			
			p = (a - Ox)/64;
			q = (b - Oy)/64;
			if( board[p][q]->piece_x_index == -1 ) return true;
			return false;			
		}		
	}else{
		if( m == 0 && n == 64 ){
			p = (toX - Ox)/64;
			q = (toY - Oy)/64 + 1;
			if( board[p][q]->piece_x_index != -1 ) return true;
			return false;				
		}		
		if( first_move ){
			if(	m == 0 && n == 128){
				p = (toX - Ox)/64;
				q = (toY - Oy)/64 + 1;
				if( board[p][q]->piece_x_index != -1 ) return true;
				
				q = (toY - Oy)/64 + 2;
				if( board[p][q]->piece_x_index != -1 ) return true;				
				return false;				
			}
		}
		if( abs(m) == 64 && n == 64){
			int g = (toX - Ox)/64 + abs(m)/m;			
			int h = (toY - Oy)/64;
			if( just_moved_pawn_x != -1){
				if( h == 4 && g >= 0 && g <= 7){
					if( board[g][h]->piece_x_index == just_moved_pawn_x 
					 && board[g][h]->piece_y_index == just_moved_pawn_y ){
					 	en_passant = true;
						return false;	
					}
				}
			}
			p = (a - Ox)/64;
			q = (b - Oy)/64;
			if( board[p][q]->piece_x_index == -1 ) return true;
			return false;			
		}		
	}
	return true;	
}

bool Pawn::is_path_blocked(int a, int b, Square* board[8][8]){
	int m = a - toX;
	int n = b - toY;
	int p, q;	
	if( isWhite ){
		if( abs(m) == 64 && n == -64){		
			return false;			
		}		
	}else{
		if( abs(m) == 64 && n == 64){
			return false;			
		}		
	}
	return true;
}

void Pawn::move_to(int a, int b, Square* board[8][8]){
	int m = (a - Ox)/64;	
	int n = (b - Oy)/64;	
	int p = (toX - Ox)/64;	
	int q = (toY - Oy)/64;
	
	toX = a;
	toY = b;
	if( first_move ){
		first_move = false;
		just_moved_pawn_x = x_index;
		just_moved_pawn_y = y_index;
	}else{
		just_moved_pawn_x = -1;
		just_moved_pawn_y = -1;		
	}
	if( n == 7 ){
		pawn_promotion_x = x_index;
		pawn_promotion_y = y_index;
	}
	
	if( n == 0 ){
		pawn_promotion_x = x_index;
		pawn_promotion_y = y_index;
	}
	
	board[m][n]->piece_x_index = x_index;
	board[m][n]->piece_y_index = y_index;
	board[m][n]->isWhite = isWhite;	
	board[p][q]->clear();
}

void Pawn::mark_path_to(int a, int b, Chess_Frame* all){
	all->check_path->append( all->board[(toX - Ox)/64][(toY - Oy)/64] );
}

bool Pawn::try_move_to(int a, int b,int &I, int &J, Chess_Frame* all){
	if( isCaptured) return false;
	if(toX == a && toY == b){
		I = -4;
		return false;
	}	
	en_passant = false;
	if( pawn_is_path_blocked(a, b, all->board) ){
		I = -3;
		return false;	
	}		
	int X = toX;
	int Y = toY;
	int m = (a - Ox)/64;	//convert to matrix of squares coordinates	
	int n = (b - Oy)/64;	//(m,n) is the destination square coordinates
	int p = (toX - Ox)/64;	//(p,q) is the current square coordinates
	int q = (toY - Oy)/64;
	bool simulate_success = true;
	if( en_passant ){
		I = just_moved_pawn_x;
		J = just_moved_pawn_y;		
		int g = (all->army[I][J]->getX() - Ox)/64;
		int h = (all->army[I][J]->getY() - Oy)/64;
		
		all->board[p][q]->clear();
		all->board[g][h]->clear();
		all->army[I][J]->isCaptured = true;
		setPos(a, b, all->board);			//simulate move to latter square
		if( all->is_king_checked(isWhite) ){
			simulate_success = false;
		}
		
		all->army[I][J]->isCaptured = false;
		all->army[I][J]->setPos(g*64 + Ox, h*64 + Oy, all->board);
		all->board[m][n]->clear();
		setPos(X, Y, all->board);		
		
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
		setPos(a,b, all->board);
		
		if( all->is_king_checked(isWhite) ){
			simulate_success = false;
		}
		
		all->army[I][J]->isCaptured = false;
		all->army[I][J]->setPos(a,b, all->board);
		setPos(X, Y, all->board);
	}
	return simulate_success;
}

void Pawn::remove(WasteBasket* basket){
	if( !isWhite ){
		isCaptured = true;
	}else{
		isCaptured = true;
	}
	basket->add_pawn(isWhite);		
}

bool Pawn::try_all_moves(Chess_Frame* all){
	if( isCaptured ) return true;
	int X = toX;
	int Y = toY;
	int I = -1, J = -1;	
	if( isWhite ){
		if(first_move)
			if( try_move_to(X, Y - 128,I, J, all) ) return false;
		if( try_move_to(X, Y + 64, I, J, all) ) return false;
		if( X + 64 < (8*64 + Ox) )  
			if( try_move_to(X + 64, Y - 64, I, J, all) ) return false;		
		if( X - 64 > Ox )
			if( try_move_to(X - 64, Y - 64, I, J, all) ) return false;			
	}else{
		if(first_move)
			if( try_move_to(X, Y + 128, I, J, all) ) return false;
		if( try_move_to(X, Y + 64, I, J, all) ) return false;
		if( X + 64 < (8*64 + Ox) )  
			if( try_move_to(X + 64, Y + 64, I, J, all) ) return false;		
		if( X - 64 > Ox )
			if( try_move_to(X - 64, Y + 64, I, J, all) ) return false;		
	}
	return true;
}
