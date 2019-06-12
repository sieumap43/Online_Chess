#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Square.h"
#include <iostream>
using namespace std;

class Queen: public Piece{
	public:
		Queen(bool is_white, int number);
		~Queen();
		void print();
		void remove(WasteBasket* basket);
		bool is_path_blocked(int a, int b, Square* board[8][8]);
		void mark_path_to(int a, int b, Chess_Frame* all);
		bool try_all_moves(Chess_Frame* all);
};
#endif
