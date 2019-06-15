#pragma once

#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

std::string getmyIP();
std::string getSubnet(std::string ip, std::string submask);



