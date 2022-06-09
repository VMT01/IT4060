#pragma once
#pragma comment(lib, "WS2_32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <signal.h>
#include <conio.h>
#include "Constants.h"

typedef struct serverInfo {
	char *host;
	u_short port;

	/* Constructor */
	serverInfo(char *_host, u_short _port): host(_host), port(_port) {}
} serverInfo;