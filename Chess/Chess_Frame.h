#ifndef CHESS_FRAME_H
#define CHESS_FRAME_H

#include "Piece.h"
#include "Square.h"
#include "WasteBasket.h"
#include "Promote_options.h"
#include "pMoves.h"
#include "Process_Moves.h"
#include <string>

/*************************************************
	Online Libraries
*************************************************/
#include "MessageHandler.h"
#include "TcpClient.h"
#include "TcpServer.h"
extern std::string MessageToBeSent;
class MessageHandler;

class Piece;
class TcpServer;
class TcpClient;
class Server_Chess;
class Chess_Frame{
	protected:
		bool promoting_pawn = false;
		
	public:
		int white_piece_captured_num;	//total number of white pieces captured
		int black_piece_captured_num;	//total number of black pieces captured
		bool player1_turn;	//determine which player is in turn
		bool playing;		//determine if a piece is being chosen
		bool change_turn;	//determine if there is a change turn
		bool check_mate;	//announce checkmate
		bool draw_game;		//announce draw

		bool has_first_turn;
		int row_index;
		int played_piece_x_index = -1;
		int played_piece_y_index = -1;
		int played_piece_toX = -1;
		int played_piece_toY = -1;

		Piece* army[2][16];	//array of 32 pointers to 32 piece instances
		Square* board[8][8];//array of 64 pointers to 64 square instances
		Path* check_path;	//pointer to an array that marks the checking path
		WasteBasket* basket;//basket containing all captured pieces
		Promote_options* prom_menu; //pointer to the promotion_menu
		
		Chess_Frame();
		~Chess_Frame();
		virtual void handleEvent(SDL_Event &e) = 0;
		void update();
		virtual void render();
		
		virtual void promote_pawn(int piece_type);
		bool is_king_checked(bool white_turn, bool mark_checkers = false);
		bool is_checkmate();
		bool is_draw();
};

class PvP_Chess:public Chess_Frame{
	public:
		PvP_Chess();
		~PvP_Chess();
		void handleEvent(SDL_Event &e);		
};



class AI_Chess:public Chess_Frame{
	public:
		Process_Moves* process;
		pMoves* pM;		
		AI_Chess();
		~AI_Chess();
		void handleEvent(SDL_Event &e);	
		void render();
		void promote_pawn(int piece_type);		
};
void Server_handle(Server_Chess* Server_ptr, int client, string msg);
class Server_Chess : public Chess_Frame
{
public:
	int enemy_promoting_flag = 0;
	Server_Chess();
	~Server_Chess();
	TcpServer* server;
	MessageHandler msg_handler;
	
	void handleEvent(SDL_Event &e);
};

class Client_Chess : public Chess_Frame
{
public:
	int enemy_promoting_flag = 0;
	Client_Chess();
	~Client_Chess();
	TcpClient* client;
	MessageHandler msg_handler;
	void handleEvent(SDL_Event &e);
};

#endif
