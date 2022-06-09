#pragma once
#pragma comment(lib, "WS2_32.lib")

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>		// exit
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>	// _beginthreadex, WaitForSingleObject
#include <signal.h>
#include <vector>
#include "Constants.h"
using std::vector;

typedef struct Acc {
	char *username;
	char status;
	bool isLogin = false;

	/* Constructor */
	Acc(char *_username, char _status): username(_username), status(_status) {}
} Acc;

typedef struct ParamInfo {
	SOCKET sock;
	char *clientIP;
	int clientPort;
	char messQueue[BUFF_SIZE];
	bool isLogin = false;
	vector<Acc> *vAcc;
	vector<Acc>::iterator userIndex;

	/* Constructor */
	ParamInfo(SOCKET _sock, char *_clientIP, int _clientPort, vector<Acc> *_vAcc): sock(_sock), clientIP(_clientIP), clientPort(_clientPort), vAcc(_vAcc) {
		strcpy_s(messQueue, BUFF_SIZE, "");
	}
} ParamInfo;