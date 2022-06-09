#include "Communicate_Helper.h"

/**
* recv() wrapper function
* @param data: Client info struct, include client socket number, client IP, client port number
* @param buff: User message
* @param size: User message length, default = BUFF_SIZE
* @param flags: recv() flags, default = 0
* @return recv() return code
*/
int Receive(ClientInfo data, char *buff, int size, int flags) {
	int ret = recv(data.sock, buff, size, flags);
	if (SOCKET_ERROR == ret) printf("Error %d: Cannot receive data from [%s:%d]\n", WSAGetLastError(), data.clientIP, data.clientPort);
	else if (0 == ret) printf("Client [%s:%d] disconnected\n", data.clientIP, data.clientPort);

	return ret;
}

/**
* send() wrapper function
* @param data: Client info struct, include client socket number, client IP, client port number
* @param buff: Server message
* @param size: Server message length, default = BUFF_SIZE (Leave size = BUFF_SIZE may create internal error)
* @param flags: send() flags, default = 0
* @return send() return code
*/
int Send(ClientInfo data, char *buff, int size, int flags) {
	int ret = send(data.sock, buff, size, flags);
	if (SOCKET_ERROR == ret) printf("Error %d: Cannot send data to [%s:%d]\n", WSAGetLastError(), data.clientIP, data.clientPort);

	return ret;
}