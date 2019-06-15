#include"portScanning.h"
/* FUNCTIONS */


std::string getmyIP()
{
	std::string line;
	std::string ip;
	std::string submask;
	std::ifstream IPFile;
	int offset;
	const char* search0 = "IPv4 Address. . . . . . . . . . . :";      // search pattern
	const char* search1 = "Subnet Mask . . . . . . . . . . . :";

	system("ipconfig > ip.txt");

	IPFile.open("ip.txt");
	if (IPFile.is_open())
	{
		while (!IPFile.eof())
		{
			getline(IPFile, line);
			if ((offset = line.find(search0, 0)) != std::string::npos)
			{
				//   IPv4 Address. . . . . . . . . . . : 1
				//1234567890123456789012345678901234567890     
				line.erase(0, 39);
				ip = line;
				//cout << line << endl;
			}
			else if ((offset = line.find(search1, 0)) != std::string::npos)
			{
				//   Subnet Mask . . . . . . . . . . . : 2
				//1234567890123456789012345678901234567890     
				line.erase(0, 39);
				submask = line;
				//cout << line << endl;
			}
		}
		IPFile.close();
	}
	return ip;
}

std::string getSubnet(std::string ip, std::string submask)
{
	char buf[INET_ADDRSTRLEN];

	// Store ip and submask in ULONG type for calculation
	struct sockaddr_in ipSocket;
	inet_pton(AF_INET, ip.c_str(), &(ipSocket.sin_addr.S_un.S_addr));
	struct sockaddr_in submaskSocket;
	inet_pton(AF_INET, submask.c_str(), &(submaskSocket.sin_addr.S_un.S_addr));
	struct sockaddr_in subnetSocket;
	subnetSocket.sin_addr.S_un.S_addr = (ipSocket.sin_addr.S_un.S_addr & submaskSocket.sin_addr.S_un.S_addr) | (~submaskSocket.sin_addr.S_un.S_addr);

	// Convert & store subnet addr in buf[] Then prints it.
	inet_ntop(AF_INET, &(subnetSocket.sin_addr), buf, INET_ADDRSTRLEN);

	return buf;

}