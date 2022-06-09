#include "Communicate_Helper.h"

int Receive(ParamInfo *data, char *buff, int size, int flags) {
	int ret = recv(data->sock, buff, size, flags);

	if (ret == SOCKET_ERROR) {
		printf("Error %d: Cannot receive data from %s:%d\n", WSAGetLastError(), data->clientIP, data->clientPort);
	} else if (ret == 0) {
		printf("Client %s:%d disconneted\n", data->clientIP, data->clientPort);
	}

	return ret;
}

int Send(ParamInfo *data, char *buff, int size, int flags) {
	int ret = send(data->sock, buff, size, flags);
	if (ret == SOCKET_ERROR) {
		printf("Error %d: Cannot send data to %s:%d\n", WSAGetLastError(), data->clientIP, data->clientPort);
	}
	return ret;
}