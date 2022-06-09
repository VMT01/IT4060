#pragma once
#include "Header.h"

void initWinSock(HWND);
SOCKET constructSocket(HWND);
void bindAddress(HWND, SOCKET);
void listenRequest(HWND, SOCKET);
SOCKET init(HWND);
void terminate(SOCKET);