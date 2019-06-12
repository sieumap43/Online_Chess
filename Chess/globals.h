#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "constants.h"
#include<string>
using namespace std;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

extern int stateID;		//show current state
extern int nextState;	//show next state

//extern bool player1_turn, playing, global_change_turn, check_mate, draw_game;

extern int just_moved_pawn_x;	//record the index of
extern int just_moved_pawn_y;	//the pawn that just moved
extern int pawn_promotion_x;	//record the index of
extern int pawn_promotion_y;	//the pawn that just moved to the bottom (to be promoted)

#endif
