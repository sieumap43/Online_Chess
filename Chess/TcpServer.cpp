#include "TcpServer.h"
#include <sstream> 

TcpServer::TcpServer(std::string ipAddress, int port, MessageReceivedHandler handler, Server_Chess* Server_ptr)
	: m_ipAddress(ipAddress), m_port(port), MessageReceived(handler), Server_ptr(Server_ptr)
{

}
TcpServer::~TcpServer()
{
	Cleanup();
}
//Send message to specified client
void TcpServer::Send(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size()+1, 0);
}
//Initiallize winsock
bool TcpServer::Init()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	//TODO: Inform caller that the error that occured 
	return wsInit == 0;
}
void TcpServer::Connecting()
{

	SOCKET listening = CreateSocket();
	if (listening == INVALID_SOCKET)
	{
		return;
	}
	//Wait for connection 
	client = WaitForConnection(listening);
	if (client != INVALID_SOCKET)
	{
		closesocket(listening);
		std::cout << "Connected" << std::endl;
	}
	return;
}
//The Main processing Loop
void TcpServer::Run()
{
	char buf[MAX_BUFFER_SIZE];
	int bytesReceived = 0;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
	if (bytesReceived > 0)
	{
		if (MessageReceived != NULL)
		{
			MessageReceived(Server_ptr, client, std::string(buf, 0, bytesReceived));
		}
	}
		
		//Loop receive/send 
}

bool TcpServer::RunNB() //Non Blocking Running
{
	char buf[MAX_BUFFER_SIZE];
	int bytesReceived = 0;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	bytesReceived = w_recv(client, buf, MAX_BUFFER_SIZE, 0);
	if (bytesReceived > 0)
	{
		if (MessageReceived != NULL)
		{
			MessageReceived(Server_ptr, client, std::string(buf, 0, bytesReceived));
		}
		return true;
	}
	return false;
}
void TcpServer::Cleanup()
{
	closesocket(client);
	WSACleanup();
}

SOCKET TcpServer::CreateSocket()
{
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != INVALID_SOCKET)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;
		//inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindOk != SOMAXCONN)
		{
			int listenOk = listen(listening, SOMAXCONN);
			if (listenOk == SOCKET_ERROR)
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return listening;
}

//Wait for a connection
SOCKET TcpServer::WaitForConnection(SOCKET listening)
{
	SOCKET client = accept(listening, NULL, NULL);
	return client;
}