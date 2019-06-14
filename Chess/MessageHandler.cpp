#include <sstream> 
#include "MessageHandler.h"
std::string MessageHandler::encode(int send_x_index, int send_y_index, int send_toPixel_X, int send_toPixel_y, int promoting_flag)
{
	std::stringstream msg_tmp;
	msg_tmp << send_x_index << "-" << send_y_index << "-" << send_toPixel_X << "-" << send_toPixel_y << "-" << promoting_flag << "-";
	return msg_tmp.str();
}

void MessageHandler::decode(std::string msg)
{
	recv_x_index = atoi(msg.substr(0, msg.find('-')).c_str());
	msg.erase(0, msg.find('-') + 1);
	recv_y_index = atoi(msg.substr(0, msg.find('-')).c_str());
	msg.erase(0, msg.find('-') + 1);
	recv_toPixel_X = atoi(msg.substr(0, msg.find('-')).c_str());
	msg.erase(0, msg.find('-') + 1);
	recv_toPixel_Y = atoi(msg.substr(0, msg.find('-')).c_str());
	msg.erase(0, msg.find('-') + 1);
	recv_promoting_flag = atoi(msg.substr(0, msg.find('-')).c_str());
}