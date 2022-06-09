#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
#define ENDING_DELIMITER "\r\n"
#define ENDING_DELIMITER_LENGTH 2