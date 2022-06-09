#include "stdafx.h"
#include "Winsock_Helper.h"

void initWinSock(HWND window) {
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		MessageBox(window, L"Winsock 2.2 is not supported", L"Error!", MB_OK);
		exit(-1);
	}
}

SOCKET constructSocket(HWND window) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock) {
		MessageBox(window, L"Cannot create server socket", L"Error!", MB_OK);
		exit(-1);
	}
	return sock;
}

void bindAddress(HWND window, SOCKET sock) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	if (bind(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		MessageBox(window, L"Cannot associate a local address with server socket.", L"Error!", MB_OK);
		exit(-1);
	}
}

void listenRequest(HWND window, SOCKET sock) {
	if (listen(sock, MAX_CLIENT) == SOCKET_ERROR) {
		MessageBox(window, L"Cannot place server socket in state LISTEN.", L"Error!", MB_OK);
		exit(-1);
	}
}

SOCKET init(HWND window) {
	initWinSock(window);
	SOCKET sock = constructSocket(window);
	bindAddress(window, sock);
	listenRequest(window, sock);
	return sock;
}

void terminate(SOCKET sock) {
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	WSACleanup();
}