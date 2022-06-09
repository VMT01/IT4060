#pragma once
#include "Header.h"

int Receive(ClientInfo, char *, int = BUFF_SIZE, int = 0);
int Send(ClientInfo, char *, int = BUFF_SIZE, int = 0);