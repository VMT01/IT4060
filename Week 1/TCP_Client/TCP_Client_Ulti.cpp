#include "TCP_Client_Ulti.h"

serverInfo getUserInput(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Error: Wrong input format. Try again with TCP_Client.exe SERVER_HOST SERVER_PORT\n");
		exit(1);
	}
	return serverInfo(argv[1], (u_short)strtoul(argv[2], NULL, 0));
}

void start(SOCKET sock) {
	char sBuff[BUFF_SIZE], rBuff[BUFF_SIZE];

	/* Insert test here */
	startReceiveMess(sock, rBuff, sBuff);
}

void startReceiveMess(SOCKET connSock, char *rBuff, char *sBuff) {
	int ret, messageLen;
	while (1) {
		/* Send message */
		printf("Send to server: ");
		gets_s(sBuff, BUFF_SIZE);
		strcat(sBuff, ENDING_DELIMITER);
		messageLen = strlen(sBuff);
		if (messageLen == 2) break;

		ret = send(connSock, sBuff, messageLen, 0);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot send data.\n", WSAGetLastError());
		}

		/* Receive echo message */
		ret = recv(connSock, rBuff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT) {
				printf("Time-out\n");
			} else {
				printf("Error %d: Cannot receive data\n", WSAGetLastError());
			}
		} else if (strlen(rBuff) > 0) {
			rBuff[ret] = 0;
			printf("Receive from server %s\n", rBuff);
		}
	}
}
