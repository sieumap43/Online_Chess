#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Square.h"
#include <iostream>
using namespace std;

class Bishop:public Piece{
	private:
	public:
		Bishop(bool is_white, int number);
		~Bishop();
		void print();
		void remove(WasteBasket* basket);
		bool is_path_blocked(int a, int b, Square* board[8][8]);
		void mark_path_to(int a, int b, Chess_Frame* all);
		bool try_all_moves(Chess_Frame* all);
};

#endif
