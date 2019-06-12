#ifndef KING_H
#define KING_H
#include "Piece.h"
#include "Square.h"

class King:public Piece{
	public:
		King(bool is_white);
		~King();
		void print();
		
		bool initiate_move_to(int a, int b, Chess_Frame* all);		
		bool is_path_blocked(int a, int b, Square* board[8][8]);		
		bool try_move_to(int a, int b, int &I, int &J, Chess_Frame* all);		
		void move_to(int a, int b, Square* board[8][8]);
		
		bool try_all_moves(Chess_Frame* all);
	protected:
		bool left_castling = false;
		bool right_castling = false;
};
#endif
