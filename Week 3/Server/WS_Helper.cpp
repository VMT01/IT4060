#include "WS_Helper.h"

/**
* Init winsock 2.2
* @return none
*/
void initWinSock() {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		exit(-1);
	}
}

/**
* Construct socket number
* @return Socket number
*/
SOCKET constructSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock) {
		printf("Error %d: Cannot create server socket.\n", WSAGetLastError());
		exit(-1);
	}
	return sock;
}

/**
* Bind server info to socket port number
* @param sock: Socket number
* @param port: Server port number
* @return none
*/
void bindAddress(SOCKET sock, u_short port) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	if (bind(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		printf("Error %d: Cannot associate a local address with server socket.\n", WSAGetLastError());
		exit(-1);
	}
}

/**
* Place server in LISTEN state
* @param sock: Socket number
* @return none
*/
void listenRequest(SOCKET sock) {
	if (listen(sock, 10) == SOCKET_ERROR) {
		printf("Error %d: Cannot place server socket in state LISTEN\n", WSAGetLastError());
		exit(-1);
	}
}

/**
* Init server
* @param port: Server port number
* @return Socket number
*/
SOCKET init(u_short port) {
	initWinSock();
	SOCKET sock = constructSocket();
	bindAddress(sock, port);
	listenRequest(sock);

	printf("Server started\n");
	return sock;
}

/**
* Release resource
* @param sock: Socket number
* @return none
*/
void terminate(SOCKET sock) {
	closesocket(sock);
	WSACleanup();
	printf("Server stopped\n");
}