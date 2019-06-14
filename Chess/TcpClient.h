#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "Chess_Frame.h"
#include "NonBlockingRecv.h"
#include "portScanning.h"
#include <vector>
#include <sstream>
#include <thread>

#define MAX_BUFFER_SIZE (49152)
class TcpClient;
class Client_Chess;
typedef void(*MessageReceivedHandlerC)(Client_Chess* Client_ptr, int socketID, std::string msg);
static bool port_is_open(std::string ip, int port);
void task(const std::string& ip, int port, TcpClient* TcpClient);
class TcpClient 
{
public:
	TcpClient(std::string ipAddress, int port, MessageReceivedHandlerC handler, Client_Chess* client_ptr);
	~TcpClient();
	//Send message to specified client
	void Send(int clientSocket, std::string msg);
	//Initiallize winsock
	bool Init();
	//The Main processing Loop
	void Run();
	bool RunNB();
	//Receive Loop
	//Scanning the Server
	std::vector<std::string> ipAddresses;
	bool serverScanning();
	bool Connecting();
	//Send back message

	//Clean up
	void Cleanup();
	SOCKET server;
	Client_Chess* client_ptr;
	//Encode or Decode value
private:
	//Create a socket
	SOCKET CreateSocket();

	//Wait for a connection
	std::string m_ipAddress;
	int			m_port;
	MessageReceivedHandlerC MessageReceived;
};