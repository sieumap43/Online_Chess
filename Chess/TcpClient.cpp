#include "TcpClient.h"


TcpClient::TcpClient(std::string ipAddress, int port, MessageReceivedHandlerC handler, Client_Chess* client_ptr)
	: m_ipAddress(ipAddress), m_port(port), MessageReceived(handler), client_ptr(client_ptr)
{

}
TcpClient::~TcpClient()
{
	Cleanup();
}
//Send message to specified client
void TcpClient::Send(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
}
//Initiallize winsock
bool TcpClient::Init()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsInit = WSAStartup(ver, &data);
	//TODO: Inform caller that the error that occured 
	return wsInit == 0;
}
bool TcpClient::Connecting()
{
	//Wait for connection 
	server = CreateSocket();
	if (server == 0)
	{
		//std::cout << "Failed Connected" << std::endl;
		return false;
	}
	else return true;
	
}
//The Main processing Loop
void TcpClient::Run()
{
	char buf[MAX_BUFFER_SIZE];
	int bytesReceived = 0;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	bytesReceived = recv(server, buf, MAX_BUFFER_SIZE, 0);

	if (bytesReceived > 0)
	{
		if (MessageReceived != NULL)
		{
			MessageReceived(client_ptr, server, std::string(buf, 0, bytesReceived));
		}
	}
}

bool TcpClient::RunNB()
{
	char buf[MAX_BUFFER_SIZE];
	int bytesReceived = 0;
	ZeroMemory(buf, MAX_BUFFER_SIZE);
	bytesReceived = w_recv(server, buf, MAX_BUFFER_SIZE, 0);

	if (bytesReceived > 0)
	{
		if (MessageReceived != NULL)
		{
			MessageReceived(client_ptr, server, std::string(buf, 0, bytesReceived));
		}
		return true;
	}
	return false;
}
void TcpClient::Cleanup()
{
	closesocket(server);
	WSACleanup();
}

SOCKET TcpClient::CreateSocket()
{
	//Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err# " << WSAGetLastError() << std:: endl;
	}

	//Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

	//Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err # " << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}
	return sock;
}

