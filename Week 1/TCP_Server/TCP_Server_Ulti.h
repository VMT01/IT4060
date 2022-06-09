#pragma once
#include "Header.h"

/**
* @function getUserInput: Handle user input from terminal
* @param [IN]argc: Argument number in terminal
* @param [IN]argv: A pointer to argument input array in terminal
* @return: Server port number 
*/
u_short getUserInput(int argc, char *argv[]);

/**
* @function run: Start connection with client
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

/**
* @function handleSplitMess: Handle split user message
* @param [IN]connSock: A connection socket with a specify client
* @param [OUT]sBuff: A pointer to send buffer array
* @return: none
*/
void handleSplitMess(SOCKET connSock, char *sBuff);