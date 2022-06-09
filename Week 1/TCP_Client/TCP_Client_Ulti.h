#pragma once
#include "Header.h"

typedef struct serverInfo {
	serverInfo(char *_host, u_short _port): host(_host), port(_port) {}
	char *host;
	u_short port;
} serverInfo;

/**
* @function getUserInput: Handle user input from terminal
* @param [IN]argc: Argument number in terminal
* @param [IN]argv: A pointer to argument input array in terminal
* @return: Struct of server information, include server host and server port
*/
serverInfo getUserInput(int argc, char *argv[]);

/**
* @function start: Start connection with client
* @param [IN]sock: Socket where server communicate with client
* @return: none
*/
void start(SOCKET sock);

/**
* @function startCommunicate: Start communicate with a specify client
* @param [IN]connSock: A connection socket with a specify client
* @param [OUT]rBuff: A pointer to receive buffer array
* @param [OUT]sBuff: A pointer to send buffer array
* @return: none
*/
void startReceiveMess(SOCKET connSock, char *rBuff, char *sBuff);