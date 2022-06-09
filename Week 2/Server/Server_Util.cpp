#pragma once
#include "Server_Util.h"
#include "Communicate_Helper.h"
#include "Server_APIs.h"

void prepareData(vector<Acc> *vAcc) {
	FILE *f = fopen("./account.txt", "r");
	if (NULL == f) {
		printf("File corrupted\n");
		exit(-1);
	}

	char str[255];
	int index;

	while (fgets(str, 255, f)) {
		index = strchr(str, ' ') - str;

		char *username = (char *)malloc((index + 1) * sizeof(char));
		strncpy_s(username, index + 1, str, index);

		vAcc->push_back(Acc(username, str[index + 1]));
	}
	fclose(f);
}

u_short getUserInput(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Error: Wrong input format. Try again with Server.exe SERVER_PORT\n");
		exit(-1);
	}
	return (u_short)strtoul(argv[1], NULL, 0);
}

void start(SOCKET *sock, vector<Acc> *vAcc) {
	sockaddr_in clientAddr;
	char clientIP[INET_ADDRSTRLEN];
	int clientAddrLen = sizeof(clientAddr), clientPort;
	HANDLE hThread;
	SOCKET connSock;

	while (1) {
		connSock = accept(*sock, (sockaddr *)&clientAddr, &clientAddrLen);
		if (connSock == SOCKET_ERROR) {
			printf("Error %d: Cannot permit incoming connection\n", WSAGetLastError());
		} else {
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
			clientPort = ntohs(clientAddr.sin_port);
			printf("Accept incoming connection from %s:%d\n", clientIP, clientPort);

			hThread = (HANDLE)_beginthreadex(0, 0, communicate, (void *)new ParamInfo(connSock, clientIP, clientPort, vAcc), 0, 0);
		}
	}

	WaitForSingleObject(hThread, INFINITE);
}

unsigned __stdcall communicate(void *param) {
	char buff[BUFF_SIZE];
	int ret;
	ParamInfo *data = (ParamInfo *)param;

	while (1) {
		ret = Receive(data, buff);
		if (ret == SOCKET_ERROR || ret == 0) {
			if (data->isLogin) {
				data->isLogin = false;
				data->userIndex->isLogin = false;
			}
			break;
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			printf("Receive from %s:%d %s\n", data->clientIP, data->clientPort, buff);

			strcat_s(data->messQueue, BUFF_SIZE, buff);
			processData(data);
		}
	}

	closesocket(data->sock);
	return 0;
}

void processData(ParamInfo *data) {
	int index, messQueueLen;
	char *p, buff[BUFF_SIZE], token[BUFF_SIZE];

	while ((p = strstr(data->messQueue, ENDING_DELIMITER)) != NULL) {
		index = p - data->messQueue;
		messQueueLen = strlen(data->messQueue);
		strncpy_s(token, BUFF_SIZE, data->messQueue, index);
		strncpy_s(data->messQueue, BUFF_SIZE, &data->messQueue[index + 2], messQueueLen - index - 2);
		
		strcpy_s(buff, BUFF_SIZE, handleMessage(token, data));
		strcat_s(buff, BUFF_SIZE, ENDING_DELIMITER);
		Send(data, buff, strlen(buff));
	}
}

char *handleMessage(char *token, ParamInfo *data) {
	char *p, value[BUFF_SIZE];
	int len = strlen(token), methodLen;

	if ((p = strstr(token, LOGIN)) == token && !data->isLogin) {
		methodLen = strlen(LOGIN) + 1;
		strncpy_s(value, BUFF_SIZE, &token[methodLen], len - methodLen);
		return handleLogin(value, data);
	} else if ((p = strstr(token, UPLOAD)) != NULL && p - token == 0) {
		methodLen = strlen(UPLOAD) + 1;
		strncpy_s(value, BUFF_SIZE, &token[methodLen], len - methodLen);
		return handleUpload(data);
	} else if ((p = strstr(token, LOGOUT)) != NULL && p - token == 0) {
		return handleLogout(data);
	} else return INVALID_REQUEST;
}