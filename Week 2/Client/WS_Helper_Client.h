#pragma once
#include "Header.h"

/**
* @function initWinSock: Init winsock 2.2
* @return none
*/
void initWinSock();

/**
* @function constructSocket: Construct socket port number
* @param sock: A pointer to socket number
* @return none
*/
void constructSocket(SOCKET *sock);

/**
* @function bindAddressToSocket: Bind server address to socket port number
* @param sock: A pointer to socket number
* @return none
*/
void setTimeout(SOCKET *sock);

/**
* @function listenRequest: Place server in LISTEN state
* @param sock: A pointer to socket number
* @param host: Server IP address
* @param port: Server port number
* @return none
*/
void connectServer(SOCKET *sock, char *host, u_short port);

/**
* @function init: Init server
* @param sock: A pointer to socket number
* @param host: Server IP address
* @param port: A pointer to server port number
* @return none
*/
void init(SOCKET *sock, char *host, u_short port);

/**
* @function terminate: Release resource
* @param sock: A pointer to socket number
* @return none
*/
void terminate(SOCKET *sock);