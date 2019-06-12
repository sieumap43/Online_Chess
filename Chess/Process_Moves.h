#include "Move.h"
#include "Chess_Frame.h"
#include "Piece.h"
#ifndef PROCESS_MOVES_H
#define PROCESS_MOVES_H

class AI_Chess;

class Process_Moves{
	public:		
		//Adds a move to the array of possible moves
		void addmove(int x_index, int y_index, int finalX, int finalY,  AI_Chess* all);
		//Evaluate a move made by a piece
		int evaluateMove(int x_index, int y_index, int a, int b, AI_Chess* all);
		//Find all of the possible moves
		bool possibleMoves(AI_Chess* all);
		//Find the Best Move
		Move findBestMove(AI_Chess* all);
		//Protect The King
		void protectTheKing(AI_Chess* all);
		
		int numofMoves = 0;

};

#endif
