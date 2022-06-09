#pragma once
#pragma comment(lib, "WS2_32.lib")

#include "stdafx.h"
#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>	// inet_pton
#include <process.h>
#include <signal.h>
#include <vector>
using std::vector;

typedef struct Acc {
	char *username;
	char status;
	bool isLogin;

	/* Constructor */
	Acc(char *_username, char _status) {
		username = _username;
		status = _status;
		isLogin = false;
	}

} Acc;

typedef struct ClientInfo {
	SOCKET sock;
	char *clientIP;
	u_short clientPort;
	char messQueue[BUFF_SIZE];
	bool isLogin;
	vector<Acc>::iterator userIndex;

	/* Constructor */
	ClientInfo() {
		sock = 0;
		isLogin = false;
		strcpy_s(messQueue, BUFF_SIZE, "");
	}

	ClientInfo(SOCKET _sock, char *_clientIP, u_short _clientPort) {
		sock = _sock;
		clientIP = _clientIP;
		clientPort = _clientPort;
		isLogin = false;
		strcpy_s(messQueue, BUFF_SIZE, "");
	}

} ClientInfo;

typedef struct ThreadInfo {
	SOCKET sock;
	int offset;

	/* Constructor */
	ThreadInfo(SOCKET _sock, int _offset) {
		sock = _sock;
		offset = _offset;
	}

} ThreadInfo;

typedef struct GlobalInfo {
	ClientInfo client[FD_SETSIZE];
	int clientCount;

	/* Constructor */
	GlobalInfo() {
		for (int i = 0; i < FD_SETSIZE; i++) client[i] = {};
		clientCount = 0;
	}

	GlobalInfo(ClientInfo _client, int _clientCount) {
		client[0] = _client;
		clientCount = _clientCount;
	}

} GlobalInfo;

typedef enum {
	CLIENT_ASSIGN_AT_FIRST_INDEX,	// 0 - Re-assign client at first slot
	CLIENT_ASSIGN_AT_EMPTY_INDEX,	// 1 - Assign client at empty slot
	CLIENT_OUT_OF_BOUND				// 2 - All slot is full
} flags;

typedef struct {
	flags flag;
	int offset;
} NewClientConnectInfo;