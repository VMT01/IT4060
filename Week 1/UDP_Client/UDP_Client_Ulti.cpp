#include "UDP_Client_Ulti.h"

serverInfo getUserInput(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Error: Wrong input format. Try again with UDP_Client.exe SERVER_HOST SERVER_PORT\n");
		exit(1);
	}
	return serverInfo(argv[1], (u_short)strtoul(argv[2], NULL, 0));
}

void start(SOCKET sock, serverInfo svInfo) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(svInfo.port);
	inet_pton(AF_INET, svInfo.host, &serverAddr.sin_addr);

	if (connect(sock, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Error %d: Cannot connect server\n", WSAGetLastError());
		exit(1);
	}

	char buff[BUFF_SIZE];
	int ret, serverAddrLen = sizeof(serverAddr), messageLen;

	while (1) {
		printf("Enter: ");
		gets_s(buff, BUFF_SIZE);
		messageLen = strlen(buff);
		if (messageLen == 0) break;

		ret = sendto(sock, buff, messageLen, 0, (sockaddr *)&serverAddr, serverAddrLen);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot send data\n", WSAGetLastError());
		}

		ret = recvfrom(sock, buff, BUFF_SIZE, 0, (sockaddr *)&serverAddr, &serverAddrLen);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT) {
				printf("Time-out\n");
			} else {
				printf("Error %d: Cannot receive message\n", WSAGetLastError());
			}
		} else if (strlen(buff) > 0) {
			buff[ret] = 0;
			handleMessage(buff);
		}
	}
}

void handleMessage(char *buff) {
	char *token = strtok(buff, "\n");
	char mess[BUFF_SIZE];
	memcpy(mess, &token[1], strlen(token) - 1);
	mess[strlen(token) - 1] = '\0';

	if (token[0] == '-') {
		printf("%s\n", mess);
	} else {
		printf("%s\n", mess);
		token = strtok(NULL, "\n");
		while (token != NULL) {
			memcpy(mess, &token[1], strlen(token) - 1);
			mess[strlen(token) - 1] = '\0';
			printf("%s\n", mess);
			token = strtok(NULL, "\n");
		}
	}
}