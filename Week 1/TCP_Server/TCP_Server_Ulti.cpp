#include "TCP_Server_Ulti.h"

char messQueue[BUFF_SIZE], token[BUFF_SIZE], clientIP[INET_ADDRSTRLEN];
int clientPort, index, messQueueLen, sum;
bool flag;

u_short getUserInput(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Error: Wrong input format. Try again with TCP_Server.exe SERVER_PORT\n");
		exit(1);
	}
	return (u_short)strtoul(argv[1], NULL, 0);
}

void start(SOCKET sock) {
	sockaddr_in clientAddr;
	char rBuff[BUFF_SIZE], sBuff[BUFF_SIZE];
	int clientAddrLen = sizeof(clientAddr);
	SOCKET connSock;

	//strcpy_s(messQueue, BUFF_SIZE, "");
	//strcpy_s(token, BUFF_SIZE, "");

	while (1) {
		connSock = accept(sock, (sockaddr *)&clientAddr, &clientAddrLen);
		if (connSock == SOCKET_ERROR) {
			printf("Error %d: Cannot permit incoming connection\n", WSAGetLastError());;
			break;
		} else {
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
			clientPort = ntohs(clientAddr.sin_port);
			printf("Accept incoming connection from %s:%d\n", clientIP, clientPort);
		}

		startReceiveMess(connSock, rBuff, sBuff);
	}
}

void startReceiveMess(SOCKET connSock, char *rBuff, char *sBuff) {
	int ret;
	while (1) {
		ret = recv(connSock, rBuff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot receive data.\n", WSAGetLastError());
			break;
		} else if (ret == 0) {
			printf("Client disconnected\n");
			break;
		} else {
			rBuff[ret] = 0;
			printf("Receive from client [%s:%d] %s\n", clientIP, clientPort, rBuff);

			/* Append message into mess queue */
			strcat_s(messQueue, BUFF_SIZE, rBuff);
			handleSplitMess(connSock, sBuff);
		}
	}
}

void handleSplitMess(SOCKET connSock, char *sBuff) {
	int ret;
	while ((index = strstr(messQueue, ENDING_DELIMITER) - messQueue) >= 0) {
		messQueueLen = strlen(messQueue);
		strncpy_s(token, BUFF_SIZE, messQueue, index);
		strncpy_s(messQueue, BUFF_SIZE, &messQueue[index + ENDING_DELIMITER_LENGTH], messQueueLen - index - ENDING_DELIMITER_LENGTH);

		sum = 0;
		flag = false;
		for (int i = 0; i < strlen(token); i++) {
			if (isalpha(token[i])) {
				flag = true;
				break;
			} else {
				sum += token[i] - '0';
			}
		}
		if (flag) strcpy_s(sBuff, BUFF_SIZE, "Failed: String contains non-number character.");
		else itoa(sum, sBuff, 10);

		/* Add ending delimiter */
		strcat_s(sBuff, BUFF_SIZE, ENDING_DELIMITER);
		printf("Send to client [%s:%d] %s", clientIP, clientPort, sBuff);
		ret = send(connSock, sBuff, strlen(sBuff), 0);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot send data.\n", WSAGetLastError());
		}
	}
}
