#pragma once
#include "Header.h"

/**
* @function initWinSock: Initiate WinSock
* @return: none
*/
void initWinSock();

/**
* @function constructSocket: Construct Socket
* @param [IN]sock: A pointer to socket where server use to create connection
* @return: none
*/
void constructSocket(SOCKET *sock);


/**
* @function constructSocket: Set timeout for client
* @param [IN]sock: A pointer to socket where server use to create connection
* @param [IN] tv: Time interval for client timeout
* @return: none
*/
void setTimeout(SOCKET *sock, int tv);

/**
* @function constructSocket: Set timeout for client
* @param [IN]sock: A pointer to socket where server use to create connection
* @param [IN]host: Server IP address
* @param [IN]port: Server port number
* @return: none
*/
void connectServer(SOCKET *sock, char *host, u_short port);

/**
* @function init: Start server
* @param [IN]sock: A pointer to socker where server use to create connection
* @param [IN]host: Server IP address
* @param [IN]port: Server port number
* @return: none
*/
void init(SOCKET *sock, char *host, u_short port);

/**
* @function terminate: Stop server
* @param [IN]sock: A pointer to socker where server use to create connection
* @return: none
*/
void terminate(SOCKET *sock);