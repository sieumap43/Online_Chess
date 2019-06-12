#include "Process_Moves.h"
#include "Piece.h"
#include "Move.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/***** ADDS A MOVE INTO THE ARRAY OF POSSIBLE MOVES *****/
void Process_Moves::addmove(int x_index, int y_index, int finalX, int finalY, AI_Chess* all)
{
	//array[] is an array of pointers to the variables in class move
	
	all->pM->array[all->pM->move_num].x_index = x_index;	//Adds the X (first) index of the Chess Piece
	all->pM->array[all->pM->move_num].y_index = y_index;	//Adds the Y (second) index of the Chess Piece
	all->pM->array[all->pM->move_num].finalX = finalX; 		//Adds the destination X coordinate
	all->pM->array[all->pM->move_num].finalY = finalY;		//Adds the destination Y coordinate
	
	//Scores the move and places it into the score variable
	all->pM->array[all->pM->move_num].score = evaluateMove(x_index, y_index, finalX, finalY, all);	
	
	//Increments the number of moves to go 
	//to the next element in the array
	all->pM->move_num++;
	
} 

/***** FINDS ALL OF THE POSSIBLE MOVES *****/
/*
	All of the possible moves of each black piece is found
	by simulating that move using the try_move_to function.
	If it is a valid move it will add that move to the 
	array of possible moves.
*/
bool Process_Moves::possibleMoves(AI_Chess* all)
{

	int I, J;
	//the color of the Chess Pieces
	int color = 1; //Color is black
	
	//Find the possible moves of all black pawns
	for(int pawn_index = 0; pawn_index < 8; pawn_index++){
		
		//If the current pawn is captured skip the piece
		if(all->army[color][pawn_index]->isCaptured) continue;
		
		int X = all->army[color][pawn_index]->getX();	//Obtain the X position of the black pawn
		int Y = all->army[color][pawn_index]->getY();	//Obtain the Y position of the black pawn
		
		//Check if pawn can move forward two spaces
		if( all->army[color][pawn_index]->first_move )	
			if( all->army[color][pawn_index]->try_move_to(X, Y + 128, I=-1, J=-1, all) ) addmove(1, pawn_index, X, Y+128, all);
		
		//Check if pawn can move forward one space
		if( all->army[color][pawn_index]->try_move_to(X, Y + 64, I=-1, J=-1, all) ) addmove(1, pawn_index, X, Y+64, all);
		
		//Check if pawn can capture enemy pieces
		if( X + 64 < (8*64 + Ox) )  
			if( all->army[color][pawn_index]->try_move_to(X + 64, Y + 64, I=-1, J=-1, all) ) addmove(1, pawn_index, X+64, Y+64, all);		
		if( X - 64 > Ox )
			if( all->army[color][pawn_index]->try_move_to(X - 64, Y + 64, I=-1, J=-1, all) ) addmove(1, pawn_index, X-64, Y+64, all);		
	}

	//Find the possible moves of all black Knight
	for(int n_index = 8; n_index < 10; n_index++){
		
		//If the current Knight is captured skip the piece
		if(all->army[color][n_index]->isCaptured) continue;
		
		int origX = all->army[color][n_index]->getX();	//Obtain the X position of the Black Knight
		int origY = all->army[color][n_index]->getY();	//Obtain the Y position of the Black Knight
		
		//Cycle through the possible moves made by Black Knight
		int X, Y, I, J, z = 1, w = 2;
		for(int g = 0; g<2; g++){
			z *= -1;		
			for(int h = 0; h<2; h++){
				w *= -1;
				X = origX + z*64;
				Y = origY + w*64;
				//If the move is out of bounds go to the next Black Knight/Piece or next move
				if( X < Ox || X > (64*7 + Ox) || Y < Oy || Y > (64*7 + Oy) ) continue;
				//Checks if Knight can move to empty space or capture piece
				if( all->army[color][n_index]->try_move_to(X, Y, I, J, all) ) addmove(color, n_index, X, Y, all);
			}
		}
		z = 2; w = 1;
		for(int g = 0; g<2; g++){
			z *= -1;		
			for(int h = 0; h<2; h++){
				w *= -1;
				X = origX + z*64;
				Y = origY + w*64;
				//If the move is out of bounds go to the next Black Knight/Piece
				if( X < Ox || X > (64*7 + Ox) || Y < Oy || Y > (64*7 + Oy) ) continue;
				//Checks if Knight can move to empty space or capture piece
				if( all->army[color][n_index]->try_move_to(X, Y, I, J, all) ) addmove(color, n_index, X, Y, all);
			}
		}
	}
	
	//The Boundaries of the Chess Board
	int top_limit = Oy;			//Upper Boundary
	int bot_limit = 64*7 + Oy;	//Lower Boundary
	int left_limit = Ox;		//Left Boundary
	int right_limit = 64*7 + Ox;//Right Boundary
	
	//Find the possible moves of all Black Bishops
	for(int b_index = 10; b_index < 12; b_index++){
		
		//If current Black Bishop is captured skip the piece
		if(all->army[color][b_index]->isCaptured) continue;
		
		int origX = all->army[color][b_index]->getX();	//Obtain the X Position of the Black Bishop
		int origY = all->army[color][b_index]->getY();	//Obtain the Y Position of the Black Bishop
		
		//Check if Black Bishop can move to empty space or capture piece [Diagonal Up-Left]
		int I, J, X = origX, Y = origY;
		while( Y >= top_limit && X < left_limit ){
			if( all->army[color][b_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, b_index, X, Y, all);
			X -= 64;	//move bishop upward to the left
			Y -= 64;
		}	
		
		//Check if Black Bishop can move to empty space or capture piece [Diagonal Up-Right]
		X = origX; Y = origY;
		while( Y >= top_limit && X <= right_limit){
			if( all->army[color][b_index]->try_move_to(X, Y, I = - 1, J = -1, all) ) addmove(color, b_index, X, Y, all);
			X += 64;	//move bishop upward to the right
			Y -= 64;
		}	
		
		//Check if Black Bishop can move to empty space or capture piece [Diagonal Down-Left]
		X = origX; Y = origY;
		while( Y <= bot_limit && X >= left_limit ){
			if( all->army[color][b_index]->try_move_to(X, Y, I, J, all) ) addmove(color, b_index, X, Y, all);
			X -= 64;	//move bishop downward to the left
			Y += 64;
		}	
		
		//Check if Black Bishop can move to empty space or capture piece [Diagonal Down-Right]
		X = origX; Y = origY;
		while( Y <= bot_limit && X <= right_limit){
			if( all->army[color][b_index]->try_move_to(X, Y, I, J, all) ) addmove(color, b_index, X, Y, all);		
			X += 64;	//move bishop downward to the right
			Y += 64;
		}
	}
	
	//Find the possible moves of all Black Rooks
	for(int r_index = 12; r_index < 14; r_index++){
		
		//If current Black Rook is captured skip the piece
		if( all->army[color][r_index]->isCaptured ) continue;
		
		int origX = all->army[color][r_index]->getX();	//Obtain the X Position of the Black Rook
		int origY = all->army[color][r_index]->getY();	//Ontain the Y Position of the Black Rook
		
		//Check if Black Rook can move to empty space or capture piece [Veritcal Up]
		int I, J, X = origX, Y = origY;
		while(Y >= top_limit ){
			if( all->army[color][r_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, r_index, X, Y, all);
			Y -= 64;	//move rook vertically upward
		}
		
		//Check if Black Rook can move to empty space or capture piece [Vertical Down]
		X = origX, Y = origY;
		while( Y <= bot_limit ){
			if( all->army[color][r_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, r_index, X, Y, all);
			Y += 64;	//move rook downward
		}
		
		//Check if Black Rook can move to empty space or capture piece [Horizontal Left]
		X = origX, Y = origY;
		while( X >= left_limit){
			if( all->army[color][r_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, r_index, X, Y, all);
			X -= 64;	//move rook to the left		
		}
		
		//Check if Black Rook can move to empty space or capture piece [Horizontal Right]
		X = origX, Y = origY;
		while( X <= right_limit){
			if( all->army[color][r_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, r_index, X, Y, all);
			X += 64;	//move rook to the right		
		}
	}
	
	//Find all the possible moves of Black Queen
	for(int q_index = 14; q_index < 15; q_index++){
		
		//If Black Queen is captured skip the piece
		if(all->army[color][q_index]->isCaptured) continue;
		
		int origX = all->army[color][q_index]->getX();	//Obtain the X Position of the Black Queen
		int origY = all->army[color][q_index]->getY();	//Obtain the Y Position of the Black Queen
		
		//Check if Black Queen can move to empty space or capture piece [Vertical Up]
		int I, J, X = origX, Y = origY;
		while(Y >= top_limit ){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			Y -= 64;	//move queen vertically upward
		}
		
		//Check if Black Queen can move to empty space or capture piece [Vertical Down]
		X = origX, Y = origY;
		while( Y <= bot_limit ){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			Y += 64;	//move queen downward
		}
		
		//Check if Black Queen can move to empty space or capture piece [Horizontal Left]
		X = origX, Y = origY;
		while( X >= left_limit){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			X -= 64;	//move queen to the left		
		}
		
		//Check if Black Queen can move to empty space or capture piece [Horizontal Right]
		X = origX, Y = origY;
		while( X <= right_limit){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			X += 64;	//move queen to the right
		}
		
		//Check if Black Queen can move to empty space or capture piece [Diagonal Up-Left]
		X = origX, Y = origY;
		while( Y >= top_limit && X < left_limit ){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			X -= 64;	//move queen upward to the left
			Y -= 64;
		}	
		
		//Check if Black Queen can move to empty space or capture piece [Diagonal Up-Right]
		X = origX; Y = origY;
		while( Y >= top_limit && X <= right_limit){
			if( all->army[color][q_index]->try_move_to(X, Y, I = - 1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			X += 64;	//move queen upward to the right
			Y -= 64;
		}	
		
		//Check if Black Queen can move to empty space or capture piece [Diagonal Down-Left]
		X = origX; Y = origY;
		while( Y <= bot_limit && X >= left_limit ){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);
			X -= 64;	//move queen downward to the left
			Y += 64;
		}	
		
		//Check if Black Queen can move to empty space or capture piece [Down-Right]
		X = origX; Y = origY;
		while( Y <= bot_limit && X <= right_limit){
			if( all->army[color][q_index]->try_move_to(X, Y, I = -1, J = -1, all) ) addmove(color, q_index, X, Y, all);		
			X += 64;	//move queen downward to the right
			Y += 64;
		}
	}
	
	//Find all possible moves for Black King
	for(int k_index = 15; k_index < 16; k_index++){
		int origX = all->army[color][k_index]->getX();	//Obtain the X Position for Black King
		int origY = all->army[color][k_index]->getY();	//Obtain the Y Position for Black King
		
		//Check if Black King can move to empty space or Capture piece
		int X = origX, Y = origY, I, J;
		for(int i = -1; i<= 1; i++){
			for(int j = -1; j<=1; j++){
				if(i == 0 && j == 0) continue;
				int a = X + i*64;
				int b = Y + j*64;
				if( a<Ox || a>(64*7 + Ox) || b<Oy || b>(64*7 + Oy) ) continue;
				if( all->army[1][k_index]->try_move_to(a, b, I = -1, J = -1, all) ) addmove(color, k_index, a,b , all);			
			}
		}
	}
	return true;
}

/***** FIND POSSIBLE MOVES TO PROTECT THE KING *****/
void Process_Moves::protectTheKing(AI_Chess* all){	

	//There are no attackers
	if( all->check_path->checker_num == 0 ) return; 
	
	//There is 1 attacker
	if( all->check_path->checker_num == 1 ){
		//Prioritize protecting the King by blocking the 
		//attacker rather than moving the King
		
		//Reset the array best move index
		all->pM->best_move_num = 0;
		//Set the greatestVal to be the lowest score possible
		int greatestVal = -100000;
		//Cycle through the array of possible moves
		for(int n = 0; n < all->check_path->size; n++){	//Index for array of path between King and attacker
			for(int i = 0; i < all->pM->move_num; i++){	//Index for array of possible moves
				//Check if the final destination XY of the move is the same as one of the squares XY in the checkpath
				
				if( ( all->pM->array[i].finalX == ( all->check_path->array[n]->x ) ) && ( all->pM->array[i].finalY == ( all->check_path->array[n]->y ) ) ){
					
					//Obtain the maximum score
					if( all->pM->array[i].score > greatestVal ){
						//If a new maximum score is found
						all->pM->resetBestMove();						//Reset the Best Move to first element
						greatestVal = all->pM->array[i].score;			//Set the greatestVal to the maximum score found
						all->pM->bestMove[all->pM->best_move_num] = i;	//store the Possible Moves Array Index
						all->pM->best_move_num++;						//Increment the Best Move Array Index to go to next element
					}
					if( all->pM->array[i].score == greatestVal ){
						//If an equally maximum score is found
						all->pM->bestMove[all->pM->best_move_num] = i;	//store the Possible Moves Array Index
						all->pM->best_move_num++;						//Increment the Best Move Array Index to go to next element
					}
				}
			}
		}
		
		//If BestMove array is still empty ONLY choice is to Move the King
		if( all->pM->bestMove[0] == -1 ){
			for(int i = 0; i < all->pM->move_num; i++){
				//Check if the Y (second) index of the moved piece is 15
				//Check if the piece is King
				if( all->pM->array[i].y_index == 15 ){
					all->pM->bestMove[all->pM->best_move_num] = i;	//store the Possible Moves Array Index
					all->pM->best_move_num++;						//Increment the Best Move Array Index
				}
			}
		}
		return;
		
	//There is more than 1 attacker	
	}else{
		//Only option is to Move the King
		for(int i = 0; i < all->pM->move_num; i++){	//Cycle through the possible moves array
			//Check if the Y (second) index of the moved piece is 15
			//Check if the piece is King
			if( all->pM->array[i].y_index == 15 ){
				all->pM->bestMove[all->pM->best_move_num] = i;	//store the Possible Moves Array Index
				all->pM->best_move_num++;						//Increment the Best Move Array Index
			}
		}
		return;	
	}
}

/***** FIND THE BEST MOVE *****/
Move Process_Moves::findBestMove(AI_Chess* all){
	numofMoves++;
	//Find the Best Move among the list of possible moves
	//Find all the possible moves
	possibleMoves(all);
	all->check_path->checker_num = 0;	//Reset the Number of Attackers
	//If the King is being checked
	if((all->is_king_checked(false, true))){	
		//Protect the King
		protectTheKing(all);
	//If the King is not being checked
	}else{
		//Set the greatestVal to be the lowest score possible
		int greatestVal = -100000;
		
		//Cycle through the array of possible moves
		for(int i = 0; i < all->pM->move_num; i++){
			//Obtain the maximum score
			if( all->pM->array[i].score > greatestVal ){
				//If a new maximum score is found
				all->pM->resetBestMove();						//Reset the Best Move to first element
				greatestVal = all->pM->array[i].score;			//Set the greatestVal to the maximum score found
				all->pM->bestMove[all->pM->best_move_num] = i;	//Store the Possible Moves Array Index
				all->pM->best_move_num++;						//Increment the Best Moves Array Index
			}else if( all->pM->array[i].score == greatestVal ){
				//If an equal maximum score is found
				all->pM->bestMove[all->pM->best_move_num] = i;	//Store the Possible Moves Array Index
				all->pM->best_move_num++;						//Increment the Best Moves Array Index
			}
		}
	}
	//Prioritize moves which do not include the King [Move the King only as a last resort]
	for(int i = 0; i < all->pM->best_move_num; i++){
		int n = all->pM->bestMove[i];
		if( all->pM->array[n].y_index == 15 ){
			all->pM->array[n].score -= 20;	//Decrease the score for a Black King Move
		}
	}
	//Choose the best move randomly
	int bmi = 0;	//Random Best Move Index
	if(all->pM->best_move_num != 0){	//Protect the Rand Function from dividing by 0
		srand(time(0));
		bmi = rand()%(all->pM->best_move_num);
	}	
	return all->pM->array[all->pM->bestMove[bmi]];
}

/***** EVALUATE THE MOVE MADE BY THE PIECE *****/
int Process_Moves::evaluateMove(int x_index, int y_index, int a, int b, AI_Chess* all)
{
	int boardValue = 0;								//Value of the Board when piece is moved
	int X = all->army[x_index][y_index]->getX();	//Obtain the Original X Position made by the piece
	int Y = all->army[x_index][y_index]->getY();	//Obtain the Original Y Position made by the piece
	int m = (a - Ox)/64;					
	int n = (b - Oy)/64;
	int p = (X - Ox)/64;
	int q = (Y - Oy)/64;
	int I, J;
	//Check if Square is empty or not
	bool emptysquare = true;
	
	//The Square is Empty
	if( all->board[m][n]->piece_x_index == -1 ){
		all->board[p][q]->clear();	 //clear former square
		
		//Simulate piece to the destination Square
		all->army[x_index][y_index]->setPos(a, b, all->board);
	
	//The Square is occupied by an enemy piece
	}else{	
		I = all->board[m][n]->piece_x_index;//Obtain X Index of White Piece in square
		J = all->board[m][n]->piece_y_index;//Obtain Y Index of White Piece in square
		
		all->board[p][q]->clear();			//clear former square
		all->army[I][J]->isCaptured = true;	//Set the White Piece in Final Square as captured
		
		//Simulate piece to the destination Square
		all->army[x_index][y_index]->setPos(a,b, all->board);
		emptysquare = false;				//The Square is not empty
	}
		
	/*******Start Evaluation**********/
	int color = 1;
	
	//Add all of the Value of the Pieces on the Board
	//after the move is made
	for(int n = -1; n < 2; n = n+2){
		//White Pieces (color = 0) have a negative n value
		//Black Pieces (color = 1) have a positive n value
		(n == -1)? color = 0: color = 1;
		//Value of Pawn Pieces
		for(int i = 0; i < 8; i++)
			if(!(all->army[color][i]->isCaptured)) boardValue += 10*n;
		//Value of Knight and Bishop Pieces
		for(int i = 8; i < 12; i++)
			if(!(all->army[color][i]->isCaptured)) boardValue += 30*n;
		//Value of Rook Pieces
		for(int i = 12; i < 14; i++)
			if(!(all->army[color][i]->isCaptured)) boardValue += 50*n;
		//Value of Queen Pieces
		if(!(all->army[color][14]->isCaptured)) boardValue += 90*n;
	}
		
	
	//White King check condition
	int WX = all->army[0][15]->getX();	//Obtain White King X Value
	int WY = all->army[0][15]->getY();	//Obtain White King Y Value
	//Checks if a black piece is attacking white king by checking 
	//if the path the piece can travel is being blocked by a white king
	if( !all->army[x_index][y_index]->is_path_blocked(WX, WY, all->board)){
		boardValue += all->army[x_index][y_index]->piecevalue;
	}
	
	//Check for safety of original position of the piece
	for(int i = 0; i < 15; i++){
		if( !all->army[0][i]->is_path_blocked(X, Y, all->board) )
			boardValue += (all->army[x_index][y_index]->piecevalue); //Add the value for original unsafe position
	}
	
	if(numofMoves < 5){
		//Set the Knight at smart positions
		if( (y_index == 8 || y_index == 9) && ( (a ==(Ox+64*2) && b ==(Oy+64*2)) || (a ==(Ox+64*5) && b ==(Oy+64*2)) ) ){
			boardValue += 10;
		}
		///Control of center board
		if( a ==(Ox+64*3)  && b == (Oy+64*3) ) boardValue +=10;
		if( a ==(Ox+64*4)  && b == (Oy+64*3) ) boardValue +=10;
		if( a ==(Ox+64*3)  && b == (Oy+64*4) ) boardValue +=10;
		if( a ==(Ox+64*4)  && b == (Oy+64*4) ) boardValue +=10;
	}
	
	//If Knight returns to original row
	if( (y_index == 8 || y_index == 9) && (b == Oy) ){
		boardValue -= 25;
	}
	
	//Check if Piece is unsafe after move is made		
	for(int i = 0; i < 15; i++){
		//Checks if a white piece is attacking the black pieces
		//by checking if the path of piece contains a black piece
		if( !all->army[0][i]->is_path_blocked(a, b, all->board) )
			boardValue -= (all->army[x_index][y_index]->piecevalue); //Subtract the Value of the piece that isn't safe
	}	
	/******End Evaluation************/
	
	if(emptysquare){
		//Clear the Piece at the destination Square
		all->board[m][n]->clear();	
		//Move Piece back to former square
		all->army[x_index][y_index]->setPos(X, Y, all->board);	
	}else{
		//Reset the isCaptured condition of the White Piece in Square
		all->army[I][J]->isCaptured = false;
		//Return the captured White Piece on the Board
		all->army[I][J]->setPos(a,b, all->board);				
		//Move Piece back to former square
		all->army[x_index][y_index]->setPos(X, Y, all->board);	
	}
	return boardValue; 
}


