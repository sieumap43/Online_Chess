#include "Chess_Frame.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"
#include "constants.h"
	
std::string MessageToBeSent;

Chess_Frame::Chess_Frame(){
	player1_turn = true;
	playing = false;
	change_turn = false;
	check_mate = false;
	draw_game = false;
	white_piece_captured_num = 0;
	black_piece_captured_num = 0;
	
	for(int i = 0; i<8; i++)
		for(int j = 0; j<8; j++){
			board[i][j] = new Square();		
			board[i][j]->setPos(i*64 + Ox, j*64 + Oy);				
		}
		
	check_path = new Path();	
	prom_menu = new Promote_options();
	basket = new WasteBasket();	
	
	for(int i = 0; i<8; i++){
		army[0][i] = new Pawn(true, i);
	}	
	army[0][8] = new Knight(true, 8);
	army[0][9] = new Knight(true, 9);
	army[0][10] = new Bishop(true, 10);
	army[0][11] = new Bishop(true, 11);
	army[0][12] = new Rook(true, 12);
	army[0][13] = new Rook(true, 13);
	army[0][14] = new Queen(true, 14);
	army[0][15] = new King(true);

	for(int i = 0; i<8; i++){
		army[1][i] = new Pawn(false, i);
	}	
	army[1][8] = new Knight(false, 8);
	army[1][9] = new Knight(false, 9);		
	army[1][10] = new Bishop(false, 10);
	army[1][11] = new Bishop(false, 11);		
	army[1][12]	= new Rook(false, 12);
	army[1][13]= new Rook(false, 13);			
	army[1][14] = new Queen(false, 14);
	army[1][15] = new King(false);

	for(int i = 0; i<8; i++){
		army[0][i]->setPos(i*64 + Ox, 6*64 + Oy, board);
	}		
	army[0][8]->setPos(1*64 + Ox, 7*64 + Oy, board);
	army[0][9]->setPos(6*64 + Ox, 7*64 + Oy, board);		
	army[0][10]->setPos(2*64 + Ox, 7*64 + Oy, board);
	army[0][11]->setPos(5*64 + Ox, 7*64 + Oy, board);	
	army[0][12]->setPos(Ox, 7*64 + Oy, board);	
	army[0][13]->setPos(7*64 + Ox, 7*64 + Oy, board);	
	army[0][14]->setPos(3*64 + Ox, 7*64 + Oy, board);
	army[0][15]->setPos(4*64 + Ox, 7*64 + Oy, board);	

	for(int i = 0; i<8; i++){
		army[1][i]->setPos(i*64 + Ox, 64 + Oy, board);
	}
	army[1][8]->setPos(1*64 + Ox, Oy, board);
	army[1][9]->setPos(6*64 + Ox, Oy, board);
	army[1][10]->setPos(2*64 + Ox, Oy, board);
	army[1][11]->setPos(5*64 + Ox, Oy, board);	
	army[1][12]->setPos(Ox, Oy, board);
	army[1][13]->setPos(7*64 + Ox, Oy, board);
	army[1][14]->setPos(3*64 + Ox, Oy, board);
	army[1][15]->setPos(4*64 + Ox, Oy, board);
}

Chess_Frame::~Chess_Frame(){
	for(int i = 0; i<2; i++)
		for(int j = 0; j<16; j++){
			delete army[i][j];
			army[i][j] = NULL;
		}
			
		
	for(int i = 0; i<8; i++)
		for(int j = 0; j<8; j++){
			delete board[i][j];
			board[i][j] = NULL;			
		}
			
	delete check_path;
	check_path = NULL;
	
	delete prom_menu;
	prom_menu = NULL;
	
	delete basket;
	basket = NULL;
}

void Chess_Frame::update(){
	for(int i = 0; i<2; i++)
		for(int j = 0; j<16; j++)
			army[i][j]->update();
			
	for(int i = 0; i<8; i++)
		for(int j = 0; j<8; j++)
			board[i][j]->update();		
}

void Chess_Frame::render(){
	for(int i = 0; i<8; i++)		//render 64 black-white squares
		for(int j = 0; j<8; j++)
			board[i][j]->render();	
				
	for(int i = 0; i<2; i++)		//render all 32 pieces
		for(int j = 0; j<16; j++)
			army[i][j]->render();
			
	basket->render();		
			
	if( promoting_pawn ){			//render promotion option if a pawn is being promoted
		prom_menu->render( player1_turn );
	}		
}

void Chess_Frame::promote_pawn(int piece_type){
	int X = army[pawn_promotion_x][pawn_promotion_y]->getX();
	int Y = army[pawn_promotion_x][pawn_promotion_y]->getY();
	
	delete army[pawn_promotion_x][pawn_promotion_y];
	army[pawn_promotion_x][pawn_promotion_y] = NULL;
	
	switch(piece_type){
		case 1:
			army[pawn_promotion_x][pawn_promotion_y] = new Queen( pawn_promotion_x == 0, pawn_promotion_y );	
			break;
		case 2:
			army[pawn_promotion_x][pawn_promotion_y] = new Rook( pawn_promotion_x == 0, pawn_promotion_y );
			break;
		case 3:
			army[pawn_promotion_x][pawn_promotion_y] = new Knight( pawn_promotion_x == 0, pawn_promotion_y );
			break;
		case 4:
			army[pawn_promotion_x][pawn_promotion_y] = new Bishop( pawn_promotion_x == 0, pawn_promotion_y );
			break;		
	}
	
	army[pawn_promotion_x][pawn_promotion_y]->setPos(X, Y, board);
	pawn_promotion_x = -1;
	pawn_promotion_y = -1;					
}

bool Chess_Frame::is_king_checked(bool white_turn, bool mark_checkers){
	
	bool is_checked = false;
	int attacker_x_index;
	int king_x_index;
	if( white_turn ){
		attacker_x_index = 1;
		king_x_index = 0;
	}else{
		attacker_x_index = 0;
		king_x_index = 1;
	}
	int X = army[king_x_index][15]->getX();	//army[0][15] is the pointer to the white king
	int Y = army[king_x_index][15]->getY();	//army[1][15] is the pointer to the black king
	for(int i = 0; i<=15; i++){
		if( army[attacker_x_index][i]->isCaptured ) continue;
		if( !army[attacker_x_index][i]->is_path_blocked(X, Y, board) ){ 
			if( mark_checkers ){
				check_path->add_checker(attacker_x_index, i);
			}
			is_checked = true;
		}
	}
	return is_checked;	
}

bool Chess_Frame::is_checkmate(){
	bool checkmate = false;
	check_path->clear();
	int king_x_index;	
	if( player1_turn ) king_x_index = 0;	
	else king_x_index = 1;
	int protector_x_index = king_x_index;
		
	int X = army[king_x_index][15]->getX();
	int Y = army[king_x_index][15]->getY();
	int checker_x_index, checker_y_index;
	
	is_king_checked( player1_turn, true);
	
	int number_of_checkers = check_path->checker_num;
	if( number_of_checkers == 1 ){
		checker_x_index = check_path->checker[0][0];
		checker_y_index = check_path->checker[1][0];
		army[checker_x_index][checker_y_index]->mark_path_to(X, Y, this);		
	}
	int I = -1, J = -1;
	for(int j = 0; j<15; j++){
		if( check_path->checker_num == 2) break;
		for(int i = 0; i < check_path->size; i++){
			int a = check_path->array[i]->x;
			int b = check_path->array[i]->y;
			if( army[protector_x_index][j]->try_move_to(a, b, I, J, this) ){
				if( I < 0 ) cout<<"An allied piece can block the check path."<<endl;
				else if( I >= 0) cout<<"An allied piece can capture the checker."<<endl;
				return false;
			}
		}
	}

	if( !army[king_x_index][15]->try_all_moves(this) ) return false;
	check_mate = true;
	return true;
}

bool Chess_Frame::is_draw(){
	if( black_piece_captured_num == 15 && white_piece_captured_num == 15 ){
		draw_game = true;
		return true;
	} 
	if( !player1_turn ){ //black's turn
		if( black_piece_captured_num <= 8 ){
			return false;
		}else{
			for(int i = 0; i<15; i++){
				if( !army[1][i]->try_all_moves(this) ){
					return false;
				}				
			}			
		}
	}else{	//white's turn
		if( white_piece_captured_num <= 8 ){
			return false;
		}else{
			for(int i = 0; i<15; i++){
				if( !army[0][i]->try_all_moves(this) ){
					return false;
				}				
			}							
		}
	}
	
	int king_x_index;	
	if( !player1_turn ) king_x_index = 1;	
	else king_x_index = 0;	
	if( !army[king_x_index][15]->try_all_moves(this) ) return false;
	
	draw_game = true;
	return true;
}

//-----------------------------------------------------//

PvP_Chess::PvP_Chess():Chess_Frame(){}
PvP_Chess::~PvP_Chess(){};

void PvP_Chess::handleEvent(SDL_Event &e){
	int piece_type = 0;
	if( !promoting_pawn ){	//if there is no pawn promotion, the game goes on as normal
		for(int i = 0; i<2; i++){
			for(int j = 0; j<16; j++){
				army[i][j]->handleEvent(e, this);
			}
		}		
	}else{		//if there is a pawn promotion, stop the game until the player decided which piece it is promoted to
		prom_menu->handleEvent(e, piece_type);
		if(piece_type != 0) change_turn = true;
	}
	
	if( change_turn ){
		change_turn = false;	//reset change_turn
		if( piece_type != 0 ){	//if the player has chosen a pawn promotion
			promote_pawn(piece_type);	//pass the option to the function
			piece_type = 0;				//reset the option
			promoting_pawn = false;		//reset the promotion signals
		}		
		if( pawn_promotion_x != -1 ){	//if there is a pawn promotion
			promoting_pawn = true;		//turn on the promotion signal
			int X = army[pawn_promotion_x][pawn_promotion_y]->getX(); //display prom_menu on the promoted pawn			
			int Y = army[pawn_promotion_x][pawn_promotion_y]->getY();
			if( !player1_turn ) prom_menu->setPos(X - 30, Y - 34);	
			else prom_menu->setPos(X - 30, Y + 64);		
		}		
		if( is_king_checked(player1_turn) ){
			int C,D;
			if( player1_turn){
				C = (army[0][15]->getX() - Ox)/64;
				D = (army[0][15]->getY() - Oy)/64;				
			}else{
				C = (army[1][15]->getX() - Ox)/64;
				D = (army[1][15]->getY() - Oy)/64;					
			}
			board[C][D]->glow_red();
			if( is_checkmate() ) cout<<"Check mate\n";						
		}else{
			if( is_draw() ) cout<<"Stalemate. Draw\n";
		}		
	}	
}

//---------------------------------------------------------//

AI_Chess::AI_Chess():Chess_Frame(){
	process = new Process_Moves();
	pM = new pMoves();
}

AI_Chess::~AI_Chess(){
	delete process; process = NULL;
	delete pM; pM = NULL;
}

void AI_Chess::handleEvent(SDL_Event &e){
	int piece_type = 0;
	if( !promoting_pawn ){	//if there is no pawn promotion, the game goes on as normal
		for(int j = 0; j<16; j++){
			army[0][j]->handleEvent(e, this);
		}			
	}else{		//if there is a pawn promotion, stop the game until the player decided which piece it is promoted to
		prom_menu->handleEvent(e, piece_type);
		if(piece_type != 0) change_turn = true;		
	}
	
	if( change_turn ){
		change_turn = false;	//reset change_turn
		if( piece_type != 0 ){	//if the player has chosen a pawn promotion
			promote_pawn(piece_type);	//pass the option to the function
			piece_type = 0;				//reset the option
			promoting_pawn = false;		//reset the promotion signals
		}		
		if( pawn_promotion_x != -1 ){	//if there is a pawn promotion
			promoting_pawn = true;		//turn on the promotion signal
			int X = army[pawn_promotion_x][pawn_promotion_y]->getX(); //display prom_menu on the promoted pawn			
			int Y = army[pawn_promotion_x][pawn_promotion_y]->getY();
			if( !player1_turn ) prom_menu->setPos(X - 30, Y - 34);	
			else prom_menu->setPos(X - 30, Y + 64);		
		}		
		if( is_king_checked(player1_turn) ){
			int C,D;
			if( player1_turn){
				C = (army[0][15]->getX() - Ox)/64;
				D = (army[0][15]->getY() - Oy)/64;
			}else{
				C = (army[1][15]->getX() - Ox)/64;
				D = (army[1][15]->getY() - Oy)/64;					
			}
			board[C][D]->glow_red();
			if( is_checkmate() ) cout<<"Check mate\n";						
		}else{
			if( is_draw() ) cout<<"Stalemate. Draw\n";
		}		
	}
	if( !player1_turn ){
		Move AI_next_move = process->findBestMove(this);
		int a = AI_next_move.finalX;
		int b = AI_next_move.finalY;
		int x_index = AI_next_move.x_index;
		int y_index = AI_next_move.y_index;
		army[x_index][y_index]->initiate_move_to(a, b, this);	
		
		pM->clear();
		player1_turn = true;	
		change_turn = true;
	}
}

void AI_Chess::render(){
	for(int i = 0; i<8; i++)		//render 64 black-white squares
		for(int j = 0; j<8; j++)
			board[i][j]->render();	
				
	for(int i = 0; i<2; i++)		//render all 32 pieces
		for(int j = 0; j<16; j++)
			army[i][j]->render();
			
	basket->render();		
			
	if( promoting_pawn ){			//render promotion option if a pawn is being promoted
		prom_menu->render( !player1_turn );
	}		
}

void AI_Chess::promote_pawn(int piece_type){
	int X = army[pawn_promotion_x][pawn_promotion_y]->getX();
	int Y = army[pawn_promotion_x][pawn_promotion_y]->getY();
	
	delete army[pawn_promotion_x][pawn_promotion_y];
	army[pawn_promotion_x][pawn_promotion_y] = NULL;
	
	if( pawn_promotion_x == 0){
		switch(piece_type){
			case 1:
				army[pawn_promotion_x][pawn_promotion_y] = new Queen( pawn_promotion_x == 0, pawn_promotion_y );	
				break;
			case 2:
				army[pawn_promotion_x][pawn_promotion_y] = new Rook( pawn_promotion_x == 0, pawn_promotion_y );
				break;
			case 3:
				army[pawn_promotion_x][pawn_promotion_y] = new Knight( pawn_promotion_x == 0, pawn_promotion_y );
				break;
			case 4:
				army[pawn_promotion_x][pawn_promotion_y] = new Bishop( pawn_promotion_x == 0, pawn_promotion_y );
				break;		
		}		
	}else if( pawn_promotion_x == 1 ){
		army[pawn_promotion_x][pawn_promotion_y] = new Queen( pawn_promotion_x == 0, pawn_promotion_y );
	}
	
	army[pawn_promotion_x][pawn_promotion_y]->setPos(X, Y, board);
	pawn_promotion_x = -1;
	pawn_promotion_y = -1;					
}


/*---------------------------------------*/
void Server_handle(Server_Chess* Server_ptr, int client, string msg)
{
	Server_ptr->msg_handler.decode(msg);
	int x_index = Server_ptr->msg_handler.recv_x_index;
	int y_index = Server_ptr->msg_handler.recv_y_index;
	int a = Server_ptr->msg_handler.recv_toPixel_X;
	int b = Server_ptr->msg_handler.recv_toPixel_Y;
	int promoting_pawn = Server_ptr->msg_handler.recv_promoting_flag;
	cout << x_index << "-" << y_index << "-" << a << "-" << b << "-" <<promoting_pawn << endl;
	Server_ptr->played_piece_x_index = x_index;
	Server_ptr->played_piece_y_index = y_index;
	Server_ptr->played_piece_toX = a;
	Server_ptr->played_piece_toY = b;
	Server_ptr->enemy_promoting_flag = promoting_pawn;
}
Server_Chess::Server_Chess() :Chess_Frame() {
	server = new TcpServer("127.0.0.1", 54000, Server_handle, this);
	if (server->Init()) { 
		server->ConnectingWithThread();
	}
	has_first_turn = true;
	if (has_first_turn) row_index = 0;
}
Server_Chess::~Server_Chess() {
	delete server; server = NULL;
};

void Server_Chess::handleEvent(SDL_Event &e)
{
	if (!server->WaitingForClient)
	{
		int piece_type = 0;
		if (!promoting_pawn) {	//if there is no pawn promotion, the game goes on as normal
			if (player1_turn == has_first_turn) {
				cout << "Playing " << endl;
				for (int j = 0; j < 16; j++)
					army[0][j]->handleEvent(e, this);
			}
			else {
				cout << "Listening" << endl;
				if (server->RunNB()) {
					if (enemy_promoting_flag == 0) {	//No promotion
						army[played_piece_x_index][played_piece_y_index]->initiate_move_to(played_piece_toX, played_piece_toY, this);
					}
					else {
						army[played_piece_x_index][played_piece_y_index]->initiate_move_to(played_piece_toX, played_piece_toY, this);
						promote_pawn(enemy_promoting_flag);
					}
					played_piece_x_index = -1;	//reset listening variables and flags
					played_piece_y_index = -1;
					played_piece_toX = -1;
					played_piece_toY = -1;
					enemy_promoting_flag = 0;
					player1_turn = has_first_turn;	//opponent officially finished his turn
				}
				else return;
			}
		}
		else {		//if there is a pawn promotion, stop the game until the player decided which piece it is promoted to
			prom_menu->handleEvent(e, piece_type);
			if (piece_type != 0) change_turn = true;
		}

		if (change_turn) {
			change_turn = false;	//reset change_turn
			if (piece_type != 0) {	//if the player has chosen a pawn promotion

				promote_pawn(piece_type);	//pass the option to the function

				MessageHandler temp;	//send promotion choice
				MessageToBeSent = temp.encode(played_piece_x_index, played_piece_y_index, played_piece_toX, played_piece_toY, piece_type);
				server->Send(server->client, MessageToBeSent);
				played_piece_x_index = -1;
				played_piece_y_index = -1;
				played_piece_toX = -1;
				played_piece_toY = -1;

				piece_type = 0;				//reset the option
				promoting_pawn = false;		//reset the promotion signals
			}
			if (pawn_promotion_x != -1) {	//if there is a pawn promotion
				promoting_pawn = true;		//turn on the promotion signal
				int X = army[pawn_promotion_x][pawn_promotion_y]->getX(); //display prom_menu on the promoted pawn			
				int Y = army[pawn_promotion_x][pawn_promotion_y]->getY();
				if (!player1_turn) prom_menu->setPos(X - 30, Y - 34);
				else prom_menu->setPos(X - 30, Y + 64);
			}
			else {
				MessageHandler temp;
				MessageToBeSent = temp.encode(played_piece_x_index, played_piece_y_index, played_piece_toX, played_piece_toY, -1);
				server->Send(server->client, MessageToBeSent);
				played_piece_x_index = -1;
				played_piece_y_index = -1;
				played_piece_toX = -1;
				played_piece_toY = -1;
			}
			if (is_king_checked(player1_turn)) {
				int C, D;
				if (player1_turn) {
					C = (army[0][15]->getX() - Ox) / 64;
					D = (army[0][15]->getY() - Oy) / 64;
				}
				else {
					C = (army[1][15]->getX() - Ox) / 64;
					D = (army[1][15]->getY() - Oy) / 64;
				}
				board[C][D]->glow_red();
				if (is_checkmate()) cout << "Check mate\n";
			}
			else {
				if (is_draw()) cout << "Stalemate. Draw\n";
			}
		}
	}
	else
	{
		
	}
}

/*--------------------------------------------------------*/
void Client_handle(Client_Chess* Client_ptr, int client, string msg)
{
	Client_ptr->msg_handler.decode(msg);
	int x_index = Client_ptr->msg_handler.recv_x_index;
	int y_index = Client_ptr->msg_handler.recv_y_index;
	int a = Client_ptr->msg_handler.recv_toPixel_X;
	int b = Client_ptr->msg_handler.recv_toPixel_Y;
	int promoting_flag = Client_ptr->msg_handler.recv_promoting_flag;
	cout << x_index << "-" << y_index << "-" << a << "-" << b << "-" <<promoting_flag << endl;
	Client_ptr->played_piece_x_index = x_index;
	Client_ptr->played_piece_y_index = y_index;
	Client_ptr->played_piece_toX = a;
	Client_ptr->played_piece_toY = b;
	Client_ptr->enemy_promoting_flag = promoting_flag;
}
Client_Chess::Client_Chess() :Chess_Frame() {
	client = new TcpClient("127.0.0.1", 54000, Client_handle, this);
	/*if (client->Init()) {
		if (!client->Connecting())
		{
			cout << "Failed to connect!Quitting...";
			nextState = STATE_INTRO;
		}
	}*/
	if (client->Init()) {
		if (client->serverScanning())
		{
			if (client->Connecting())
			{
				client->Send(client->server, "101-");
			}
			else
			{
				cout << "Failed connected";
				nextState = STATE_INTRO;
			}
		}
		else
		{
			cout << "No Server Found";
			nextState = STATE_INTRO;
		}
	}
	has_first_turn = false;
	if (has_first_turn) row_index = 0;
	else row_index = 1;
}
Client_Chess::~Client_Chess() {
	delete client; client = NULL;
};

void Client_Chess::handleEvent(SDL_Event &e)
{
	int piece_type = 0;
	if (!promoting_pawn) {	//if there is no pawn promotion, the game goes on as normal
		if (player1_turn == has_first_turn) {
			cout << "Playing" << endl;
			for (int j = 0; j < 16; j++)
				army[row_index][j]->handleEvent(e, this);
		}
		else {
			cout << "Listening" << endl;
			if (client->RunNB()) {
				if (enemy_promoting_flag == 0) {	//No promotion
					army[played_piece_x_index][played_piece_y_index]->initiate_move_to(played_piece_toX, played_piece_toY, this);
				}
				else {
					army[played_piece_x_index][played_piece_y_index]->initiate_move_to(played_piece_toX, played_piece_toY, this);
					promote_pawn(enemy_promoting_flag);
				}
				played_piece_x_index = -1;
				played_piece_y_index = -1;
				played_piece_toX = -1;
				played_piece_toY = -1;
				enemy_promoting_flag = 0;
				player1_turn = has_first_turn;
			}
			else return;
		}
	}
	else {		//if there is a pawn promotion, stop the game until the player decided which piece it is promoted to
		prom_menu->handleEvent(e, piece_type);
		if (piece_type != 0) change_turn = true;
	}

	if (change_turn) {
		change_turn = false;	//reset change_turn
		if (piece_type != 0) {	//if the player has chosen a pawn promotion
			promote_pawn(piece_type);	//pass the option to the function

			MessageHandler temp;
			cout << played_piece_x_index << endl;
			MessageToBeSent = temp.encode(played_piece_x_index, played_piece_y_index, played_piece_toX, played_piece_toY, piece_type);
			client->Send(client->server, MessageToBeSent);
			played_piece_x_index = -1;
			played_piece_y_index = -1;
			played_piece_toX = -1;
			played_piece_toY = -1;

			piece_type = 0;				//reset the option
			promoting_pawn = false;		//reset the promotion signals
		}
		if (pawn_promotion_x != -1) {	//if there is a pawn promotion
			promoting_pawn = true;		//turn on the promotion signal
			int X = army[pawn_promotion_x][pawn_promotion_y]->getX(); //display prom_menu on the promoted pawn			
			int Y = army[pawn_promotion_x][pawn_promotion_y]->getY();
			if (!player1_turn) prom_menu->setPos(X - 30, Y - 34);
			else prom_menu->setPos(X - 30, Y + 64);
		}
		else {
			MessageHandler temp;
			cout << played_piece_x_index << endl;
			MessageToBeSent = temp.encode(played_piece_x_index, played_piece_y_index, played_piece_toX, played_piece_toY, -1);
			client->Send(client->server, MessageToBeSent);
			played_piece_x_index = -1;
			played_piece_y_index = -1;
			played_piece_toX = -1;
			played_piece_toY = -1;
		}
		if (is_king_checked(player1_turn)) {
			int C, D;
			if (player1_turn) {
				C = (army[0][15]->getX() - Ox) / 64;
				D = (army[0][15]->getY() - Oy) / 64;
			}
			else {
				C = (army[1][15]->getX() - Ox) / 64;
				D = (army[1][15]->getY() - Oy) / 64;
			}
			board[C][D]->glow_red();
			if (is_checkmate()) cout << "Check mate\n";
		}
		else {
			if (is_draw()) cout << "Stalemate. Draw\n";
		}
	}
}