#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Square.h"
#include <iostream>
using namespace std;

class Pawn:public Piece{
	protected:
		bool en_passant = false;
	public:
		Pawn(bool is_white, int number);
		~Pawn();
		void print();

		bool initiate_move_to(int a, int b, Chess_Frame* all);	
		bool is_path_blocked(int a, int b, Square* board[8][8]);	//this function is used in the is_check function in Chess_Frame
		bool pawn_is_path_blocked(int a, int b, Square* board[8][8]); //a special is_path_blocked function for the pawn, this version is used in the try_move_to function	
					
		bool try_move_to(int a, int b, int &I, int &J, Chess_Frame* all);		
		void move_to(int a, int b, Square* board[8][8]);	
		void remove(WasteBasket* basket);			
		
		void mark_path_to(int a, int b, Chess_Frame* all);
		bool try_all_moves(Chess_Frame* all);
};

#endif
