#pragma once
#include "Header.h"

void initWinSock();
SOCKET constructSocket();
void bindAddress(SOCKET, u_short);
void listenRequest(SOCKET);
SOCKET init(u_short);
void terminate(SOCKET);