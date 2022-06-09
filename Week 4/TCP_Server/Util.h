#pragma once
#include "Header.h"

void handleRequest(ClientInfo);
void encryptRequest(ClientInfo, int, char *);
void decryptRequest(ClientInfo, int, char *);