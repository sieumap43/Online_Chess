#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "globals.h"
#include "LTexture.h"
#include <iostream>
using namespace std;

class Button{
	public:
		virtual ~Button();
		void setPos(int a, int b);
		void setText(string text);
		virtual void handleEvent(SDL_Event &e) = 0;
		virtual void render();
		int getX();
		int getY();
		int getWidth();
		int getHeight();
	protected:
		int x,y;
		int width, height;
		bool click; //show if the mouse if over the button or not
};

class PvP_Button:public Button{
	public:
		PvP_Button();
		~PvP_Button();
		void handleEvent(SDL_Event &e);
};

class Server_Button :public Button {
public:
	Server_Button();
	~Server_Button();
	void handleEvent(SDL_Event &e);
};

class AI_Button:public Button{
	public:
		AI_Button();
		~AI_Button();
		void handleEvent(SDL_Event &e);
};

class LAN_Button :public Button {
public:
	LAN_Button();
	~LAN_Button();
	void handleEvent(SDL_Event &e);
};

class Client_Button :public Button {
public:
	Client_Button();
	~Client_Button();
	void handleEvent(SDL_Event &e);
};

class Quit_Button:public Button{
	public:
		Quit_Button();
		~Quit_Button();
		void handleEvent(SDL_Event &e);
};

class Back_Button:public Button{
	public:
		Back_Button();
		~Back_Button();
		void handleEvent(SDL_Event &e);
		void render();
};
#endif
