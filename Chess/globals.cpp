#include "globals.h"
using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

int stateID = STATE_NULL;
int nextState = STATE_NULL;

int just_moved_pawn_x = -1;
int just_moved_pawn_y = -1;
int pawn_promotion_x = -1;
int pawn_promotion_y = -1;
