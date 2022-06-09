#include "TCP_WS_Helper_Client.h"

void initWinSock() {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		exit(1);
	}
}

void constructSocket(SOCKET *sock) {
	*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*sock == INVALID_SOCKET) {
		printf("Error %d: Cannot create server socket.\n", WSAGetLastError());
		exit(1);
	}
}

void setTimeout(SOCKET *sock, int tv) {
	setsockopt(*sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(int));
}

void connectServer(SOCKET *sock, char *host, u_short port) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, host, &serverAddr.sin_addr);

	/* Request to connect server*/
	if (connect(*sock, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Error %d: Cannot connect server\n", WSAGetLastError());
		exit(1);
	}
}

void init(SOCKET *sock, char *host, u_short port) {
	initWinSock();
	constructSocket(sock);
	setTimeout(sock, 10000);
	connectServer(sock, host, port);
	printf("Connected server!\n");
}

void terminate(SOCKET *sock) {
	closesocket(*sock);
	WSACleanup();
	printf("Server stop!\n");
}