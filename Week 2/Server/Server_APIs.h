#pragma once
#include "Header.h"

/**
* @function handleLogin: Handle user login request
* @param username: Username
* @param data: A pointer to thread parameter
* @return: Login response code (10, 11, 12, 13)
*/
char *handleLogin(char *username, ParamInfo *data);

/**
* @function handleLogin: Handle user upload post request
* @param data: A pointer to thread parameter
* @return: Response code (20, 21)
*/
char *handleUpload(ParamInfo *data);

/**
* @function handleLogin: Handle user logout request
* @param data: A pointer to thread parameter
* @return: Response code (30, 21)
*/char *handleLogout(ParamInfo *data);