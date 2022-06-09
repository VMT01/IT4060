#include "UDP_Server_Ulti.h"

u_short getUserInput(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Error: Wrong input format. Try again with UDP_Server.exe SERVER_PORT\n");
		exit(1);
	}
	return (u_short)strtoul(argv[1], NULL, 0);
}

void start(SOCKET sock) {
	sockaddr_in clientAddr;
	char buff[BUFF_SIZE], clientIP[INET_ADDRSTRLEN], ans[BUFF_SIZE];
	int ret, clientAddrLen = sizeof(clientAddr), clientPort;

	while (1) {
		/* Receive message */
		ret = recvfrom(sock, buff, BUFF_SIZE, 0, (sockaddr *)&clientAddr, &clientAddrLen);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot receive data\n", WSAGetLastError());
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
			clientPort = ntohs(clientAddr.sin_port);
			printf("Receive from client [%s:%d] %s\n", clientIP, clientPort, buff);

			findAddress(ans, buff);
			/* Send answer */
			ret = sendto(sock, ans, strlen(ans), 0, (sockaddr *)&clientAddr, sizeof(clientAddr));
			if (ret == SOCKET_ERROR) {
				printf("Error %d: Cannot send data\n", WSAGetLastError());
			}
		}
	}
}

void findAddress(char *ans, char *host) {
	addrinfo *result, hints;
	int rc;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	rc = getaddrinfo(host, NULL, &hints, &result);

	if (rc == 0) {
		char *message = "+IP Addresses:\n";
		strcpy_s(ans, strlen(ans) + strlen(message) + 1, message);
		genAnswer(ans, result);
	}
	else if (rc == 11001) {
		char *message = "-Not found information\n";
		strcpy_s(ans, strlen(ans) + strlen(message) + 1, message);
	}
	else printf("Error %d: Unknown error occurred\n", WSAGetLastError());
}

void genAnswer(char *ans, addrinfo *addr) {
	char ipStr[INET_ADDRSTRLEN];
	sockaddr_in *address = (sockaddr_in *)addr->ai_addr;
	inet_ntop(AF_INET, &address->sin_addr, ipStr, sizeof(ipStr));

	strcat_s(ans, strlen(ans) + 2, "+");
	strcat_s(ipStr, strlen(ipStr) + 2, "\n");
	strcat_s(ans, strlen(ans) + strlen(ipStr) + 1, ipStr);

	if (addr->ai_next) genAnswer(ans, addr->ai_next);
}