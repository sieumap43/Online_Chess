#include "TcpClient.h"
static bool port_is_open(std::string ip, int port) {
	struct sockaddr_in address;  //the libc network address data structure 
	short int sock = -1;          //file descriptor for the network socket 
	fd_set fdset;
	struct timeval tv;
	
	address.sin_family = AF_INET;
	//	address.sin_addr.s_addr = inet_addr(ip.c_str());  assign the address 
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &address.sin_addr);

	//translate int2port num 
	sock = socket(AF_INET, SOCK_STREAM, 0);

	//Change no non-blocking mode 
	u_long iMode = 1;
	int iResult = ioctlsocket(sock, FIONBIO, &iMode);
	if (iResult != NO_ERROR)
		printf("ioctlsocket failed with error: %ld\n", iResult);
	//fcntl(sock, F_SETFL, O_NONBLOCK);

	connect(sock, (struct sockaddr *)&address, sizeof(address));
	//cout << "Task " << ip << "done. " << endl;
	FD_ZERO(&fdset);
	FD_SET(sock, &fdset);
	tv.tv_sec = 0;             // timeout 
	tv.tv_usec = 50;

	if (select(sock + 1, NULL, &fdset, NULL, &tv) >0)
	{
		int so_error;
		socklen_t len = sizeof so_error;

		getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&so_error, &len);

		if (so_error == 0) {
			closesocket(sock);
			return true;
		}
		else {
			closesocket(sock);
			return false;
		}
	}
	return false;
}

void task(const std::string& ip, int port, TcpClient* TcpClient) {

	if (port_is_open(ip, port))
	{
		std::cout << ip << ":" << port << " is open\n";
		TcpClient->ipAddresses.push_back(ip);
	}
}
bool TcpClient::serverScanning()
{
	std::string ip;
	std::string subnet;
	ip = getmyIP();
	string tmp_ip = ip.erase(ip.find_last_of('.') + 1, 3);
	const std::string ip_prefix = tmp_ip;
	const int port = 54000;

	std::vector<std::thread *> tasks;
	for (int i = 0; i<255; i++) {
		std::ostringstream ip_temp;
		ip_temp << ip_prefix << i;
		tasks.push_back(new std::thread(task, ip_temp.str(), port, this));
	}
	for (int i = 0; i<255; i++) {
		tasks[i]->join();
		delete tasks[i];
	}
	if (ipAddresses.size())
	{
		cout << ipAddresses[0];
		m_ipAddress = ipAddresses[0];
		return true;
	}
	return false;
}
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





