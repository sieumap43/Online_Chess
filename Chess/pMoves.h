#ifndef PMOVES_H
#define PMOVES_H

#include "Move.h"

class pMoves
{
	public:
		pMoves();
		~pMoves();
		
		Move array[100];	//Array of possible moves
		int bestMove[100];	//Array of indexes containing best moves
		
		void resetBestMove();
		void clear();		//Clear every information
				
		int move_num = 0;	//counter for how many moves have been added into array
		int best_move_num = 0;	//counter for how many moves have been added into bestMove
		int bmi; //Best Move Index used for all->pM->array[all->pM->bestMove[bmi]];
		
};

#endif
