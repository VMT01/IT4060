#include "Communicate_Helper.h"

int Receive(SOCKET *sock, char *buff, int size, int flags) {
	int ret = recv(*sock, buff, size, flags);

	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT) printf("Time-out\n");
		else printf("Error %d: Cannot receive data\n", WSAGetLastError());
	}

	return ret;
}

int Send(SOCKET *sock, char *buff, int size, int flags) {
	int ret = send(*sock, buff, size, flags);
	if (ret == SOCKET_ERROR) {
		printf("Error %d: Cannot send data to server\n", WSAGetLastError());
	}
	return ret;
}