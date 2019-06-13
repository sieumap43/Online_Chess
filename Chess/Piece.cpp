#include<string>
#include<iostream>
#include<cmath>
#include "Piece.h"
#include "constants.h"
using namespace std;

Piece::Piece(bool is_white){
	isWhite = is_white;
	x = 8*size;
	y = 8*size;
	toX = x;
	toY = y;
	face.w = size;
	face.h = size;
	piecevalue = 0;
}

Piece::~Piece(){}

int Piece::getX(){
	return toX;
}

int Piece::getY(){
	return toY;
}

void Piece::print(){}

void Piece::setPos(int a, int b, Square* board[8][8]){
	x = a;
	y = b;
	toX = a;
	toY = b;
	int m = (a - Ox)/64;
	int n = (b - Oy)/64;
	board[m][n]->isWhite = isWhite;
	board[m][n]->piece_x_index = x_index;
	board[m][n]->piece_y_index = y_index;	
}

void Piece::handleEvent(SDL_Event &e, Chess_Frame* all){
	if(isCaptured) return;
	if(all->player1_turn != isWhite) return;
	if(!all->playing || chosen){
		if(e.type == SDL_MOUSEBUTTONDOWN && !mouse_pressing && !chosen && !all->playing){	//clicked on board
			int a,b;
			SDL_GetMouseState(&a, &b);
			if( a < Ox || a > (64*8 + Ox) || b < Oy || b > (64*8 + Oy) ) return;	// click outside the board
			if( (a>x) && (a<x + size) && (b>y) && (b<y + size) ){	//click on the piece (hit click)
				mouse_pressing = true;	//when mouse_pressing == true, SDL_MOUSEBUTTONDOWN is not registered
				chosen = true;
				all->playing = true;
				all->board[(toX - Ox)/64][(toY - Oy)/64]->glow_green();
			}else if(!chosen){									//click outside the piece (miss click)
				mouse_pressing = true;
			}
		}else if(e.type == SDL_MOUSEBUTTONDOWN && !mouse_pressing && chosen && all->playing){// make a move
			int a,b;
			SDL_GetMouseState(&a, &b);
			all->board[(toX - Ox)/64][(toY - Oy)/64]->stop_glowing_green();			
			if (this->initiate_move_to(a, b, all)) change_turn = true;
/*			{
				change_turn = true;
				if (is_online) {
					MessageHandler temp;
					MessageToBeSent = temp.encode(this->x_index, this->y_index, a, b);
				}
			}*/
			mouse_pressing = true;
			chosen = true;
			all->playing = true;
			release_1 = true;
		}		
		else if(e.type == SDL_MOUSEBUTTONUP && mouse_pressing && chosen && all->playing && !release_1){	//mouse button release after hit click
			mouse_pressing = false;
			chosen = true;
			release_1 = true;
		}				
		else if(e.type == SDL_MOUSEBUTTONUP && mouse_pressing && !chosen && !all->playing && !release_1){	//mouse button release after miss click
			mouse_pressing = false;
			chosen = false;
			all->playing = false;				
			release_1 = false;
		}	
		else if(e.type == SDL_MOUSEBUTTONUP && mouse_pressing && chosen && all->playing & release_1){	//mouse button release after a move
			mouse_pressing = false;
			chosen = false;
			all->playing = false;
			release_1 = false;
			if(change_turn){
				all->player1_turn = !all->player1_turn;		//change player's turn
				change_turn = false;
				all->change_turn = true;
				all->played_piece_toX = toX;
				all->played_piece_toY = toY;
				all->played_piece_x_index = x_index;
				all->played_piece_y_index = y_index;
			}
			all->check_path->clear(); //clear path to make the next move
		}				
	}
}

void Piece::update(){
	if( toX - x > 5 ) x += vel;
	else if( toX - x < -5 ) x -= vel;
	else x = toX;
	
	if( toY - y > 5 ) y += vel;
	else if( toY - y < -5 ) y -= vel;
	else y = toY;
}

void Piece::render(){
	if( !isCaptured ) sprite_sheet_texture.render(x, y, &face);
}

bool Piece::initiate_move_to(int a, int b, Chess_Frame* all){
	if( a < Ox || a > (64*8 + Ox) || b<Oy || b > (64*8 + Oy) ) return false;
	a = a/64*64;
	b = b/64*64;	
	int m = (a - Ox)/64;
	int n = (b - Oy)/64;
	int p = (toX - Ox)/64;
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

bool Piece::is_path_blocked(int a, int b, Square* board[8][8]){return false;}

bool Piece::try_move_to(int a, int b,int &I, int &J, Chess_Frame* all){
	if( isCaptured ) return false;
	if(toX == a && toY == b){
		I = -4;
		return false;
	}	
	if( is_path_blocked(a, b, all->board) ){
		I = -3;
		return false;	
	}		
	int X = toX;
	int Y = toY;
	int m = (a - Ox)/64;
	int n = (b - Oy)/64;
	int p = (toX - Ox)/64;
	int q = (toY - Oy)/64;
	bool simulate_success = true;	
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


void Piece::move_to(int a, int b, Square* board[8][8]){
	int m = (a - Ox)/64;
	int n = (b - Oy)/64;
	int p = (toX - Ox)/64;
	int q = (toY - Oy)/64;
	
	toX = a;
	toY = b;
	just_moved_pawn_x = -1;
	just_moved_pawn_y = -1;
	board[m][n]->piece_x_index = x_index;
	board[m][n]->piece_y_index = y_index;
	board[m][n]->isWhite = isWhite;	
	board[p][q]->clear();
}

void Piece::remove(WasteBasket* basket){}
	
void Piece::mark_path_to(int a, int b, Chess_Frame* all){}	

bool Piece::try_all_moves(Chess_Frame* all){return true;}
