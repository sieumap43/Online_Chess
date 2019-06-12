#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"
#include "Square.h"

class Rook: public Piece{
	public:
		Rook(bool is_white, int number);
		~Rook();
		void print();
		void remove(WasteBasket* basket);			
		bool is_path_blocked(int a, int b, Square* board[8][8]);
		void move_to(int a, int b, Square* board[8][8]);
		void mark_path_to(int a, int b, Chess_Frame* all);
		bool try_all_moves(Chess_Frame* all);
	protected:
};
#endif
