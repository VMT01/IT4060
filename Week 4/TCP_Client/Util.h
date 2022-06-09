#pragma once
#include "Header.h"

Input getUserInput(int, char *[]);
void start(SOCKET);
void encryptReq(SOCKET, char *, char *);
void decryptReq(SOCKET, char *, char *);