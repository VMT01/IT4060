#include "UDP_WS_Helper_Client.h"

void initWinSock() {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		exit(1);
	}
}

void constructSocket(SOCKET *sock) {
	*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (*sock == INVALID_SOCKET) {
		printf("Error %d: Cannot create client socket\n", WSAGetLastError());
		system("pause");
		exit(1);
	}
}

void init(SOCKET *sock) {
	initWinSock();
	constructSocket(sock);
	printf("Client started!\n");
}

void terminate(SOCKET *sock) {
	closesocket(*sock);
	WSACleanup();
}