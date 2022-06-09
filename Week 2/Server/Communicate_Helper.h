#pragma once
#include "Header.h"

/**
* @function Receive: recv() wrapper function
* @param data: A pointer to thread parameter
* @param buff: A pointer to user message
* @param size: Size of user message, default = BUFF_SIZE
* @param flags: recv() flags, default = 0
* @return: recv() return code
*/
int Receive(ParamInfo *data, char *buff, int size = BUFF_SIZE, int flags = 0);

/**
* @function Send: send() wrapper function
* @param data: A pointer to thread parameter
* @param buff: A pointer to server message
* @param size: Size of server message, default = BUFF_SIZE
               Warning: Leave size = BUFF_SIZE may create internal error
* @param flags: recv() flags, default = 0
* @return: send() return code
*/
int Send(ParamInfo *data, char *buff, int size = BUFF_SIZE, int flags = 0);