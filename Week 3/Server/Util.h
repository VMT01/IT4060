#pragma once
#include "Header.h"

void prepareData();
u_short getUserInput(int, char *[]);
void start(SOCKET);
NewClientConnectInfo handleNewConnection(SOCKET, char *, u_short);
unsigned __stdcall communicate(void *);
void processData(ClientInfo *);
char *handleMessage(ClientInfo *, char *);