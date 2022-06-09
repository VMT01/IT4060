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
* @function bindAddressToSocket: BindAddressToSocket
* @param [IN]sock: A pointer to socker where server use to create connection
* @param [IN]port: Server port number
* @return: none
*/
void bindAddressToSocket(SOCKET *sock, u_short port);

/**
* @function init: Start server
* @param [IN]sock: A pointer to socker where server use to create connection
* @param [IN]port: Server port number
* @return: none
*/
void init(SOCKET *sock, u_short port);

/**
* @function terminate: Stop server
* @param [IN]sock: A pointer to socker where server use to create connection
* @return: none
*/
void terminate(SOCKET *sock);