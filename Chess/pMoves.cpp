#include "pMoves.h"
#include <iostream>
using namespace std;

pMoves::pMoves(){
	
	//Set all of the variables in the array and bestMove with a value
	
	for(int i = 0; i < 100; i++){
		array[i].x_index = -1;
		array[i].y_index = -1;
		array[i].finalX = -1;
		array[i].finalY = -1;
		array[i].score = -100000;
	}
	for(int i = 0; i < 100; i++){
		bestMove[i] = -1;
	}

}

pMoves::~pMoves(){}

/*
	Reset the Values of BestMove
*/
void pMoves::resetBestMove(){
	best_move_num = 0;
	for(int i = 0; i < 100; i++) bestMove[i] = -1;
}


/*
	Reset Every Variable in pMoves Class
*/
void pMoves::clear(){
	for(int i = 0; i < 100; i++){
		array[i].x_index = -1;
		array[i].y_index = -1;
		array[i].finalX = -1;
		array[i].finalY = -1;
		array[i].score = -100000;
	}
	for(int i = 0; i < 100; i++){
		bestMove[i] = -1;
	}
	move_num = 0;
	best_move_num = 0;
}
