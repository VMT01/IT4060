#pragma once
#include "Header.h"

/**
* @function initWinSock: Initiate WinSock
* @return: none
*/
void initWinSock();

/**
* @function constructSocket: Construct Socket
* @param [IN]sock: A pointer to socker where server use to create connection
* @return: none
*/
void constructSocket(SOCKET *sock);

/**
* @function init: Start server
* @param [IN]sock: A pointer to socker where server use to create connection
* @return: none
*/
void init(SOCKET *sock);

/**
* @function terminate: Stop server
* @param [IN]sock: A pointer to socker where server use to create connection
* @return: none
*/
void terminate(SOCKET *sock);