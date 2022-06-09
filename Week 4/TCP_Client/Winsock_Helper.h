#pragma once
#include "Header.h"

void initWinSock();
SOCKET constructSocket();
void setTimeout(SOCKET);
void connectServer(SOCKET, char *, u_short);
SOCKET init(char *, u_short);
void terminate(SOCKET);