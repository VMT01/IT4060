#pragma once
#include "WS_Helper_Server.h"

void initWinSock() {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		exit(-1);
 	}
}

void constructSocket(SOCKET *sock) {
	*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*sock == INVALID_SOCKET) {
		printf("Error %d: Cannot create server socket.\n", WSAGetLastError());
		exit(-1);
	}
}

void bindAddressToSocket(SOCKET *sock, u_short *port) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(*port);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);
	if (bind(*sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		printf("Error %d: Cannot associate a local address with server socket.\n", WSAGetLastError());
		exit(1);
	}
}

void listenRequest(SOCKET *sock) {
	if (listen(*sock, 10) == SOCKET_ERROR) {
		printf("Error %d: Cannot place server socket in state LISTEN\n", WSAGetLastError());
		exit(1);
	}
}

void init(SOCKET *sock, u_short *port) {
	initWinSock();
	constructSocket(sock);
	bindAddressToSocket(sock, port);
	listenRequest(sock);

	printf("Server started!\n");
}

void terminate(SOCKET *sock) {
	closesocket(*sock);
	WSACleanup();
	printf("Server stop!\n");
}
