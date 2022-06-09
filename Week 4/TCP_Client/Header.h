#pragma once
#pragma comment(lib, "WS2_32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define BUFF_SIZE 8192
#define TIME_INTERVAL 10000
#define ENDING_DELIMITER "\r\n"

typedef struct Input {
	char *host;
	u_short port;

	/* Constructor */
	Input(char *_host, u_short _port) {
		host = _host;
		port = _port;
	}

} Input;