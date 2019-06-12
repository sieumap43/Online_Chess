#ifndef PIECE_H
#define PIECE_H

#include "include.h"
#include <iostream>;
#include <string>
#include "SDL.h"
#include "LTexture.h"
#include "Square.h"
#include "WasteBasket.h"
#include "Chess_Frame.h"
#include "globals.h"
#include "MessageHandler.h"

extern std::string MessageToBeSent;

class MessageHandler;
class Chess_Frame;
class Piece{
	protected:
		bool chosen = false;
		bool mouse_pressing = false;	//a variable to prevent repeating register of mouse event when user holds a mouse button
		bool release_1 = false;			//a variable to distinguish different mouse button release events
		bool change_turn = false;
		const int size = 64;
		int x_index, y_index;	//the row, column indices of the piece itself in the army array (army[2][16])
		int x,y;				//current coordinates
		int toX, toY;			//destination coordinates (when the piece is not moving, toX = x and toY = y)
		const int vel = 10;		//velocity
		SDL_Rect face;			//the piece's face inside the sprite sheet
	public:
		bool isCaptured = false;		//shows if the piece is captured
		int piecevalue = 0;	
		bool isWhite;			//show the piece's color
		bool first_move = true;	//show if the piece has moved for the first time
		bool is_online = false;
		Piece(bool is_white);
		virtual ~Piece();
		int getX();
		int getY();		
		virtual void print();	//print the piece's name	
		void setPos(int a, int b, Square* board[8][8]);
		
		void handleEvent(SDL_Event &e, Chess_Frame* all);	//receice mouse/keyboard actions from the user (input part)		
		void update();	//process the action (logic part)
		void render();	//render onto the screen (drawing part)
		
		virtual	bool initiate_move_to(int a, int b, Chess_Frame* all);	//start checking the validity of a move
		virtual bool is_path_blocked(int a, int b, Square* board[8][8]);//check if the move is within move ability and if there is any piece blocking the way		
		virtual bool try_move_to(int a, int b, int &I, int &J, Chess_Frame* all);	//check if the move will expose the king to a check (which makes it an invalid move)
		virtual void move_to(int a, int b, Square* board[8][8]);	//if all conditions satisfied, pick up the piece and move it	
		virtual void remove(WasteBasket* basket);	//remove the piece when it's captured

		virtual void mark_path_to(int a, int b, Chess_Frame* all);	//mark the squares that is between the current position and point (a,b)		
		virtual bool try_all_moves(Chess_Frame* all);	//try all possible moves. This method is used in evaluating draw situation.
};

#endif
