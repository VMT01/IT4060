#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define BUFF_SIZE 2048
#define TIME_INTERVAL "10000"
#define ENDING_DELIMITER "\r\n"
#define ENDING_DELIMITER_LENGTH 2