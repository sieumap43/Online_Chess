#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "Chess_Frame.h"
#include "TcpServer.h"
#include "NonBlockingRecv.h"
#define MAX_BUFFER_SIZE (49152)
class TcpClient;
class Client_Chess;
typedef void(*MessageReceivedHandlerC)(Client_Chess* Client_ptr, int socketID, std::string msg);

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