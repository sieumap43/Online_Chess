#pragma once
#include <string>
class MessageHandler
{
public:
	MessageHandler() {}
	~MessageHandler() {}
	std::string encode(int send_x_index, int send_y_index, int send_toPixel_X, int send_toPixel_y);
	void decode(std::string msg);
	int recv_x_index;
	int recv_y_index;
	int recv_toPixel_X;
	int recv_toPixel_Y;
};
