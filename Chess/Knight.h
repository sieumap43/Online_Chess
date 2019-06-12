#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Square.h"
#include <iostream>
using namespace std;

class Knight:public Piece{
	private:
	public:
		Knight(bool is_white, int number);
		~Knight();
		void print();
		void remove(WasteBasket* basket);		
		bool is_path_blocked(int a, int b, Square* board[8][8]);
		void mark_path_to(int a, int b, Chess_Frame* all);
		bool try_all_moves(Chess_Frame* all);
};

#endif
