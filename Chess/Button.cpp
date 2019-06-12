#include "Button.h"

Button::~Button(){}

int Button::getX(){
	return x;
}

int Button::getY(){
	return y;
}

int Button::getWidth(){
	return width;
}

int Button::getHeight(){
	return height;
}

void Button::setPos(int a, int b){
	x = a;
	y = b;
}

void Button::setText(string text){
}

void Button::render(){
	if( !click ){
		SDL_Rect square = {0, 0, width, height};
		button_texture.render(x, y, &square);
	}else{
		SDL_Rect square = {0, height*2, width, height};
		button_texture.render(x, y, &square);
	}
}

//-----------------------------------------------------------------------------//

PvP_Button::PvP_Button(){
	x = 0;
	y = 0;
	width = button_texture.getWidth();
	height = button_texture.getHeight()/3;
	click = false;
}

PvP_Button::~PvP_Button(){}

void PvP_Button::handleEvent(SDL_Event &e){
	if( e.type == SDL_MOUSEMOTION ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a<=x || a>=(x + width) || b<=y || b>=(y + height) ){	//mouse is outside the button
			click = false;
			return;	
		}
		click = true;
	}else if( e.type == SDL_MOUSEBUTTONDOWN ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a>x && a<(x + width) && b>y && b<(y + height) ){	//mouse clicks on the button
			nextState = STATE_PVP_BOARD;
		}
	}	
}

//-----------------------------------------------------------------------------//

AI_Button::AI_Button(){
	x = 0;
	y = 0;
	width = button_texture.getWidth();
	height = button_texture.getHeight()/3;
	click = false;	
}

AI_Button::~AI_Button(){}

void AI_Button::handleEvent(SDL_Event &e){
	if( e.type == SDL_MOUSEMOTION ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a<x || a>(x + width) || b<y || b>(y + height) ){
			click = false;
			return;	//mouse is outside the button
		}
		click = true;
	}else if( e.type == SDL_MOUSEBUTTONDOWN ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a>x && a<(x + width) && b>y && b<(y + height) ){
			nextState = STATE_AI_BOARD;
		}
	}	
}
//-----------------------------------------------------------------------------//

Quit_Button::Quit_Button(){
	x = 0;
	y = 0;
	width = button_texture.getWidth();
	height = button_texture.getHeight()/3;
	click = false;
}

Quit_Button::~Quit_Button(){}

void Quit_Button::handleEvent(SDL_Event &e){
	if( e.type == SDL_MOUSEMOTION ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a<x || a>(x + width) || b<y || b>(y + height) ){
			click = false;
			return;	//mouse is outside the button
		}
		click = true;
	}else if( e.type == SDL_MOUSEBUTTONDOWN ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a>x && a<(x + width) && b>y && b<(y + height) ){
			nextState = STATE_EXIT;
		}
	}		
}

//-----------------------------------------------------------------------------//

Back_Button::Back_Button(){
	x = 0;
	y = 0;
	width = back_button_texture.getWidth();
	height = back_button_texture.getHeight();
}

Back_Button::~Back_Button(){}

void Back_Button::handleEvent(SDL_Event &e){
	if( e.type == SDL_MOUSEBUTTONDOWN ){
		int a, b;
		SDL_GetMouseState(&a, &b);
		if( a>x && a<(x + width) && b>y && b<(y + height) ){
			nextState = STATE_INTRO;
		}
	}
}

void Back_Button::render(){
	back_button_texture.render(x, y);	
}

//-----------------------------------------------------------------------------//
LAN_Button::LAN_Button() {
	x = 0;
	y = 0;
	width = button_texture.getWidth();
	height = button_texture.getHeight() / 3;
	click = false;
}

LAN_Button::~LAN_Button() {}

void LAN_Button::handleEvent(SDL_Event &e) {
	if (e.type == SDL_MOUSEMOTION) {
		int a, b;
		SDL_GetMouseState(&a, &b);
		if (a <= x || a >= (x + width) || b <= y || b >= (y + height)) {	//mouse is outside the button
			click = false;
			return;
		}
		click = true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		int a, b;
		SDL_GetMouseState(&a, &b);
		if (a > x && a<(x + width) && b>y && b < (y + height)) {	//mouse clicks on the button
			nextState = STATE_LAN_OPTION;
		}
	}
}
//-----------------------------------------------------------------------------//

Server_Button::Server_Button() {
	x = 0;
	y = 0;
	width = button_texture.getWidth();
	height = button_texture.getHeight() / 3;
	click = false;
}

Server_Button::~Server_Button() {}

void Server_Button::handleEvent(SDL_Event &e) {
	if (e.type == SDL_MOUSEMOTION) {
		int a, b;
		SDL_GetMouseState(&a, &b);
		if (a <= x || a >= (x + width) || b <= y || b >= (y + height)) {	//mouse is outside the button
			click = false;
			return;
		}
		click = true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		int a, b;
		SDL_GetMouseState(&a, &b);
		if (a>x && a<(x + width) && b>y && b<(y + height)) {	//mouse clicks on the button
			nextState = STATE_SERVER;
		}
	}
}

//-----------------------------------------------------------------------------//

Client_Button::Client_Button() {
	x = 0;
	y = 0;
	width = button_texture.getWidth();
	height = button_texture.getHeight() / 3;
	click = false;
}

Client_Button::~Client_Button() {}

void Client_Button::handleEvent(SDL_Event &e) {
	if (e.type == SDL_MOUSEMOTION) {
		int a, b;
		SDL_GetMouseState(&a, &b);
		if (a <= x || a >= (x + width) || b <= y || b >= (y + height)) {	//mouse is outside the button
			click = false;
			return;
		}
		click = true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		int a, b;
		SDL_GetMouseState(&a, &b);
		if (a>x && a<(x + width) && b>y && b<(y + height)) {	//mouse clicks on the button
			nextState = STATE_CLIENT;
		}
	}
}


