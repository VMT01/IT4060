#pragma once
#include "Header.h"

/**
* @function prepareData: Prepare data from account.txt and store in RAM
* @param vAcc: A pointer to vector store account informations
* @return none
*/
void prepareData(vector<Acc> *vAcc);

/**
* @function getUserInput: Get user input from terminal
* @param argc: argument count
* @param argv: argument value array
* @return server port number
*/
u_short getUserInput(int argc, char *argv[]);

/**
* @function start: Start the magic, atleast for me :D
* @param sock: A pointer to socket number
* @param vAcc: A pointer to vector store account informations 
* @return none
*/
void start(SOCKET *sock, vector<Acc> *vAcc);

/**
* @function communicate: Start the thread for specific client
* @param param: A pointer to thread parameter
* @return default 0
*/
unsigned __stdcall communicate(void *param);

/**
* @function processData: Handle bytestream message and send response to client
* @param data: A pointer to thread parameter
* @return none
*/
void processData(ParamInfo *data);

/**
* @function handleMessage: Handle single user request
* @param token: A request of user get from messQueue bytestream
* @param data: A pointer to thread parameter
* @return: Server response code
*/
char *handleMessage(char *token, ParamInfo *data);