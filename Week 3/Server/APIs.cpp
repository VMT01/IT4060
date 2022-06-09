#include "APIs.h"

/**
* Handle user login request
* @param data: A pointer to client information
* @param username: Username
* @return: Login response code (10, 11, 12, 13)
*/
char *handleLogin(ClientInfo *data, char *username, vector<Acc> *vAcc) {
	if (data->isLogin) return LOGIN_DUPLICATE;
	
	vector<Acc>::iterator it = vAcc->begin();
	while (it != vAcc->end()) {
		if (strcmp(it->username, username) == 0) {
			if (it->status == '0') {
				if (it->isLogin) return LOGIN_DUPLICATE;
				data->isLogin = true;
				data->userIndex = it;
				it->isLogin = true;
				return LOGIN_SUCCESS;
			} else if (it->status == '1') return LOGIN_FORBIDDEN;
		}
		it++;
	}
	return LOGIN_EMPTY_ACC;
}

/**
* Handle user upload post request
* @param data: A pointer to client information
* @return: Response code (20, 21)
*/
char *handleUpload(ClientInfo *data) {
	if (data->isLogin) return UPLOAD_SUCCESS;
	return UPLOAD_FAIL;
}

/**
* Handle user logout request
* @param data: A pointer to client information
* @return: Response code (30, 21)
*/
char *handleLogout(ClientInfo *data) {
	if (data->isLogin) {
		data->userIndex->isLogin = false;
		data->isLogin = false;
		return LOGOUT_SUCCESS;
	}
	return LOGOUT_FAIL;
}