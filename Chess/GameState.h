#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "globals.h"
#include "LTexture.h"
#include "GIF.h"
#include "SDL.h"
#include "Button.h"
#include "Chess_Frame.h"
using namespace std;

class GameState{
	public:
		virtual void handleEvent(SDL_Event &e) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual ~GameState(){};		
	protected:
};

extern GameState *currentState;

void set_next_state(int newState);
void change_state();

class Intro:public GameState{
	public:
		Intro();
		~Intro();
		void handleEvent(SDL_Event &e);
		void update();
		void render();
	private:
		Button* pvp_button;
		Button* ai_button;
		Button* quit_button;
		
};

class PvP_Board:public GameState{
	public:
		PvP_Board();
		~PvP_Board();
		void handleEvent(SDL_Event &e);
		void update();
		void render();
	private:
		Chess_Frame* all;
		Button* back_button;
		GIF* black_won_text;
		GIF* white_won_text;
		GIF* draw_text;
};
void draw_board();

class AI_Board:public GameState{
	public:
		AI_Board();
		~AI_Board();
		void handleEvent(SDL_Event &e);
		void update();
		void render();
	private:
		Chess_Frame* all;
		Button* back_button;
		GIF* black_won_text;
		GIF* white_won_text;
		GIF* draw_text;
};	

class Server_Board :public GameState {
public:
	Server_Board();
	~Server_Board();
	void handleEvent(SDL_Event &e);
	void update();
	void render();
private:
	Chess_Frame* all;
	Button* back_button;
	GIF* black_won_text;
	GIF* white_won_text;
	GIF* draw_text;
};

class Client_Board :public GameState {
public:
	Client_Board();
	~Client_Board();
	void handleEvent(SDL_Event &e);
	void update();
	void render();
private:
	Chess_Frame* all;
	Button* back_button;
	GIF* black_won_text;
	GIF* white_won_text;
	GIF* draw_text;
};
#endif
