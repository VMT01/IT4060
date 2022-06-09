#pragma once
#include "Header.h"

typedef struct serverInfo {
	serverInfo(char *_host, u_short _port) : host(_host), port(_port) {}
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
* @function run: Start connection with client
* @param [IN]sock: Socket where server communicate with client
* @param [IN]svInfo: Server information
* @return: none
*/
void start(SOCKET sock, serverInfo svInfo);

/**
* @function run: Start connection with client
* @param [IN]buff: A pointer to buffer message
* @return: none
*/
void handleMessage(char *buff);