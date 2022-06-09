#pragma once
#include "Header.h"

/**
* @function getUserInput: Get user input from terminal
* @param argc: argument count
* @param argv: argument value array
* @return server info, include server host and server port
*/
serverInfo getUserInput(int argc, char *argv[]);

/**
* @function start: Start the magic, atleast for me :D
* @param sock: A pointer to socket number
* @return none
*/
void start(SOCKET *sock);

/**
* @function genOption: generate option to terminal for user
* return none
*/
void genOption();

/**
* @function handleOption: Handle option from user input
* @param sock: A pointer to socket number
* return breakable flag
*/
bool handleOption(SOCKET *sock);

/**
* @function sendRequest: Send user request
* @param sock: A pointer to socket number
* @param method: method user choose
* @param req: User input
* return none
*/
void sendRequest(SOCKET *sock, char *method, char *req);

/**
* @function handleResponse: Handle response from server
* @param sock: A pointer to socket number
* return none
*/
void handleResponse(SOCKET *sock);