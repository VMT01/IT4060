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
* @function findAddress: Find every IP address
* @param [OUT]ans: A pointer to answer string
* @param [IN]host: A pointer to host string
* @return: none
*/
void findAddress(char *ans, char *host);

/**
* @function genAnswer: Create answer
* @param [OUT]ans: A pointer to answer string
* @param [IN]addr: A pointer to address struct
* @return: none
*/
void genAnswer(char *ans, addrinfo *addr);