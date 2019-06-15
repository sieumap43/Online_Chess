#pragma once
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include "MessageHandler.h"
#include "Chess_Frame.h"	
#include "NonBlockingRecv.h"
#include <thread>

class Server_Chess;
#define MAX_BUFFER_SIZE (49152)
class TcpServer;
static void ListeningValue(TcpServer* ptrServer);
//TODO: Callback to data received
typedef void(*MessageReceivedHandler)(Server_Chess* Server_ptr, int socketID, std::string msg);


class TcpServer
{
public:
	TcpServer(std::string ipAddress, int port, MessageReceivedHandler handler, Server_Chess* Server_ptr);
	TcpServer() {}
	TcpServer(std::string ipAddress, int port) :m_ipAddress(ipAddress), m_port(port) {}
	~TcpServer();
	//Send message to specified client
	void Send(int clientSocket, std::string msg);
	//Initiallize winsock
	bool Init();
	//The Main processing Loop
	void Run();
	bool RunNB();
	void Connecting();
	void ConnectingWithThread();
	bool WaitingForClient;
	
	//Receive Loop
	//Send back message
	//Clean up
	void Cleanup();
	SOCKET client;
	Server_Chess* Server_ptr;
	//Encode or Decode value
private:
	//Create a socket
	SOCKET CreateSocket();

	//Wait for a connection
	SOCKET WaitForConnection(SOCKET listening);
	std::string m_ipAddress;
	int			m_port;
	MessageReceivedHandler MessageReceived;
	
};