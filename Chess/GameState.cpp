#include "GameState.h"

GameState *currentState = NULL;

void set_next_state( int newState ){
	if( nextState != STATE_EXIT){
		nextState = newState;
	}
}

void change_state(){
	if( nextState != STATE_NULL ){
		if( nextState != STATE_EXIT ){
			delete currentState;	//delete current state to make room for the next state
		}
		stateID = nextState; //change the currrent state status
		switch( nextState ){
			case STATE_INTRO:
				currentState = new Intro();
				break;
			case STATE_PVP_BOARD:
				currentState = new PvP_Board();
				break;
			case STATE_AI_BOARD:
				currentState = new AI_Board();
				break;
			case STATE_SERVER:
				currentState = new Server_Board();
				break;
			case STATE_CLIENT:
				currentState = new Client_Board();
				break;
		} 
		if (stateID == nextState)
		{
			nextState = STATE_NULL; //set nextState to NULL
		}
			
	}
}

//------------------------------------------------------------------------------------//

Intro::Intro(){
		/*pvp_button = new PvP_Button();
		ai_button = new AI_Button();*/
		pvp_button = new Server_Button();
		ai_button = new Client_Button();
		quit_button = new Quit_Button();

		int X = ( SCREEN_WIDTH - pvp_button->getWidth() )/2;
		int Y = ( SCREEN_HEIGHT - pvp_button->getHeight() )/2;
		pvp_button->setPos(X, Y - 64);	
		ai_button->setPos(X, Y + 64);	
		quit_button->setPos(X, Y + 192);					
}

Intro::~Intro(){
	delete pvp_button; pvp_button = NULL;
	delete ai_button; ai_button = NULL;
	delete quit_button; quit_button = NULL;
}

void Intro::handleEvent(SDL_Event &e){
	pvp_button->handleEvent(e);
	ai_button->handleEvent(e);
	quit_button->handleEvent(e);
}

void Intro::update(){
}

void Intro::render(){
	pvp_button->render();
	int X = pvp_button->getX() + ( pvp_button->getWidth() - pvp_text.getWidth() )/2;
	int Y = pvp_button->getY() + ( pvp_button->getHeight() - pvp_text.getHeight() )/2;	
	pvp_text.render(X, Y);

	ai_button->render();
	ai_button->render();
	X = ai_button->getX() + ( ai_button->getWidth() - pvc_text.getWidth() )/2;
	Y = ai_button->getY() + ( ai_button->getHeight() - pvc_text.getHeight() )/2;
	pvc_text.render(X, Y);	
	
	quit_button->render();
	X = quit_button->getX() + ( quit_button->getWidth() - quit_text.getWidth() )/2;
	Y = quit_button->getY() + ( quit_button->getHeight() - quit_text.getHeight() )/2;		
	quit_text.render(X, Y);
	
	X = ( SCREEN_WIDTH - title_texture.getWidth() )/2;
	Y = ( SCREEN_HEIGHT - title_texture.getHeight() )/2 - 192;	
	title_texture.render(X, Y);
	
}

//------------------------------------------------------------------------------------//

PvP_Board::PvP_Board(){
	just_moved_pawn_x = -1;
	just_moved_pawn_y = -1;
	pawn_promotion_x = -1;
	pawn_promotion_y = -1;	
	
	//load all necessary textures, graphics and objects
	all = new PvP_Chess();
	back_button = new Back_Button();
	back_button->setPos(0, 0);
	
	white_won_text = new GIF(true);
	black_won_text = new GIF(false);
	draw_text = new GIF(true, true);
	
	int X = (SCREEN_WIDTH - white_won_text->getWidth() )/2;
	int Y = 0;
	white_won_text->setPos(X, Y);
	black_won_text->setPos(X, Y);	
	draw_text->setPos(X, Y);
	
}

PvP_Board::~PvP_Board(){
	delete all; all = NULL;
	delete back_button; back_button = NULL;
	delete black_won_text; black_won_text = NULL;
	delete white_won_text; white_won_text = NULL;
	delete draw_text; draw_text = NULL;
}

void PvP_Board::handleEvent(SDL_Event &e){
	all->handleEvent(e);
	back_button->handleEvent(e);
	
	if( all->check_mate ){
		if( !all->player1_turn ) white_won_text->show_gif();
		else black_won_text->show_gif();
	}
	if( all->draw_game ){
		draw_text->show_gif();
	}
}

void PvP_Board::update(){
	all->update();
	
	white_won_text->update();
	black_won_text->update();
	draw_text->update();
}

void PvP_Board::render(){
	draw_board();
	all->render();
	
	white_won_text->render();
	black_won_text->render();
	draw_text->render();
		
	back_button->render();
}

void draw_board(){
	int square_size = 64;    //Drawing the chess all->board
	for(int j = 0; j<8; j++){//Drawing from left to right, top to bottom
		for(int i = 0; i<8; i++){
			SDL_Rect square = {square_size*i + Ox, square_size*j + Oy, square_size, square_size};//Start point: (
			if( (i+j)%2 == 0){
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderFillRect(renderer, &square);
			}else{
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(renderer, &square);
			}
		}
	}	
}

//-----------------------------------------------------//

AI_Board::AI_Board(){
	just_moved_pawn_x = -1;
	just_moved_pawn_y = -1;
	pawn_promotion_x = -1;
	pawn_promotion_y = -1;	
	
	all = new AI_Chess();
	back_button = new Back_Button();
	back_button->setPos(0, 0);
	
	white_won_text = new GIF(true);
	black_won_text = new GIF(false);
	draw_text = new GIF(true, true);
	
	int X = (SCREEN_WIDTH - white_won_text->getWidth() )/2;
	int Y = 0;
	white_won_text->setPos(X, Y);
	black_won_text->setPos(X, Y);	
	draw_text->setPos(X, Y);
	
}

AI_Board::~AI_Board(){
	delete all; all = NULL;
	delete back_button; back_button = NULL;
	delete black_won_text; black_won_text = NULL;
	delete white_won_text; white_won_text = NULL;
	delete draw_text; draw_text = NULL;
}

void AI_Board::handleEvent(SDL_Event &e){
	all->handleEvent(e);
	back_button->handleEvent(e);
	
	if( all->check_mate ){
		if( all->player1_turn ) white_won_text->show_gif();
		else black_won_text->show_gif();
	}
	if( all->draw_game ){
		draw_text->show_gif();
	}
}

void AI_Board::update(){
	all->update();
	
	white_won_text->update();
	black_won_text->update();
	draw_text->update();
}

void AI_Board::render(){
	draw_board();
	all->render();
	
	white_won_text->render();
	black_won_text->render();
	draw_text->render();
		
	back_button->render();
}

/*------------------------------------------------------*/
Server_Board::Server_Board() {
	just_moved_pawn_x = -1;
	just_moved_pawn_y = -1;
	pawn_promotion_x = -1;
	pawn_promotion_y = -1;

	//load all necessary textures, graphics and objects
	all = new Server_Chess();
	back_button = new Back_Button();
	back_button->setPos(0, 0);

	white_won_text = new GIF(true);
	black_won_text = new GIF(false);
	draw_text = new GIF(true, true);

	int X = (SCREEN_WIDTH - white_won_text->getWidth()) / 2;
	int Y = 0;
	white_won_text->setPos(X, Y);
	black_won_text->setPos(X, Y);
	draw_text->setPos(X, Y);

}

Server_Board::~Server_Board() {
	delete all; all = NULL;
	delete back_button; back_button = NULL;
	delete black_won_text; black_won_text = NULL;
	delete white_won_text; white_won_text = NULL;
	delete draw_text; draw_text = NULL;
}

void Server_Board::handleEvent(SDL_Event &e) {
	all->handleEvent(e);
	back_button->handleEvent(e);

	if (all->check_mate) {
		if (!all->player1_turn) white_won_text->show_gif();
		else black_won_text->show_gif();
	}
	if (all->draw_game) {
		draw_text->show_gif();
	}
}

void Server_Board::update() {
	all->update();

	white_won_text->update();
	black_won_text->update();
	draw_text->update();
}

void Server_Board::render() {
	draw_board();
	all->render();

	white_won_text->render();
	black_won_text->render();
	draw_text->render();

	back_button->render();
}

/*-------------------------------*/
Client_Board::Client_Board() {
	just_moved_pawn_x = -1;
	just_moved_pawn_y = -1;
	pawn_promotion_x = -1;
	pawn_promotion_y = -1;

	//load all necessary textures, graphics and objects
	all = new Client_Chess();
	back_button = new Back_Button();
	back_button->setPos(0, 0);

	white_won_text = new GIF(true);
	black_won_text = new GIF(false);
	draw_text = new GIF(true, true);

	int X = (SCREEN_WIDTH - white_won_text->getWidth()) / 2;
	int Y = 0;
	white_won_text->setPos(X, Y);
	black_won_text->setPos(X, Y);
	draw_text->setPos(X, Y);

}

Client_Board::~Client_Board() {
	delete all; all = NULL;
	delete back_button; back_button = NULL;
	delete black_won_text; black_won_text = NULL;
	delete white_won_text; white_won_text = NULL;
	delete draw_text; draw_text = NULL;
}

void Client_Board::handleEvent(SDL_Event &e) {
	all->handleEvent(e);
	back_button->handleEvent(e);

	if (all->check_mate) {
		if (!all->player1_turn) white_won_text->show_gif();
		else black_won_text->show_gif();
	}
	if (all->draw_game) {
		draw_text->show_gif();
	}
}

void Client_Board::update() {
	all->update();

	white_won_text->update();
	black_won_text->update();
	draw_text->update();
}

void Client_Board::render() {
	draw_board();
	all->render();

	white_won_text->render();
	black_won_text->render();
	draw_text->render();

	back_button->render();
}