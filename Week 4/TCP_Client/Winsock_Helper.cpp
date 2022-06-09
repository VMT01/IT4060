#include "stdafx.h"
#include "Header.h"

void initWinSock() {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		exit(-1);
	}
}

SOCKET constructSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock) {
		printf("Cannot create server socket\n");
		exit(-1);
	}
	return sock;
}

void setTimeout(SOCKET sock) {
	int tv = TIME_INTERVAL;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(int));
}

void connectServer(SOCKET sock, char *host, u_short port) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, host, &serverAddr.sin_addr);

	if (connect(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		printf("Cannot connect server\n");
		exit(-1);
	}
}

SOCKET init(char *host, u_short port) {
	initWinSock();
	SOCKET sock = constructSocket();
	setTimeout(sock);
	connectServer(sock, host, port);
	printf("Connected server\n");

	return sock;
}

void terminate(SOCKET sock) {
	closesocket(sock);
	WSACleanup();
	printf("Disconnected server\n");
}