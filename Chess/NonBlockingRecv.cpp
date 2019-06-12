#include "NonBlockingRecv.h"

/*
Use instead of recv for non-blocking functionality
Usage:
1. Include the following libraries
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
2. Parameters passed into w_recv is exactly the same as recv()
Instead of:
int bytesReceived = recv(clientSocket, buf, 4096, 0);
Use:
int bytesReceived = w_recv(clientSocket, buf, 4096, 0);
3. Note: UNLIKE recv(). w_recv()'s zero (0) output does NOT mean error
So please do not check for error as follow:
if (bytesReceived == 0)
{
cout << "Client disconnected." << endl;
break;
}
*/

int w_recv(unsigned s, void* ph, int len, int flags)
{
	fd_set r, e;
	struct timeval tval;
	int i, retval, done = 0, total = 0;

	while (!done) {
		FD_ZERO(&r); FD_ZERO(&e);
		FD_SET(s, &r); FD_SET(s, &e);
		tval.tv_sec = 0;
		tval.tv_usec = 0;
		retval = select(s + 1, &r, NULL, &e, &tval);
		if (retval == 0) {
			//Timeout elapsed with no activity
			return 0;
		}
		if (retval == -1) {
			//Socket error with select().
			return -1;
		}
		if (FD_ISSET(s, &e)) {
			//some other TCP/IP error triggered select()
			return -1;
		}
		if (FD_ISSET(s, &r)) {
			//data is available on the socket  Gather it up
			i = recv(s, ((char*)ph) + total, len - total, flags);
			if (i == -1) {
				//Socket error with recv().
				return -1;
			}
			if (i == 0) {
				//something is wrong.  select trigged but there is no data
				return 0;
			}
			//loop until all requested data is received
			total += i;
			//if (total == len) {
			done = 1;
			//}
		}
	}//done
	return total;
}