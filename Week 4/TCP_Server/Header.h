#pragma once
#pragma comment(lib, "WS2_32.lib")

#include "TCP_Server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define WM_SOCKET WM_USER + 1
#define SERVER_PORT 6600
#define SERVER_ADDR "127.0.0.1"
#define MAX_CLIENT 1024
#define BUFF_SIZE 8192
#define ENDING_DELIMITER "\r\n"

typedef struct {
	SOCKET sock;
	FILE *f;
	char messQueue[BUFF_SIZE] = "";
} ClientInfo;