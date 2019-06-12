#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "LTexture.h"

enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_PVP_BOARD,
	STATE_AI_BOARD,
	STATE_LAN_OPTION,
	STATE_SERVER,
	STATE_CLIENT,
    STATE_EXIT,
};

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 640;
const int FRAMES_PER_SECOND = 180;
const int Ox = (SCREEN_WIDTH - 64*8)/2;		//x-origin of the board
const int Oy = (SCREEN_HEIGHT - 64*8)/2;	//y-origin of the board

#endif
