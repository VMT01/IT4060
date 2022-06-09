#pragma once
#include "Server_APIs.h"

char *handleLogin(char *username, ParamInfo *data) {
	vector<Acc>::iterator it = data->vAcc->begin();
	while (it != data->vAcc->end()) {
		if (strcmp(it->username, username) == 0) {
			if (it->status == '0') {
				if (it->isLogin) return LOGIN_DUPLICATE;
				data->isLogin = true;
				data->userIndex = it;
				it->isLogin = true;
				return LOGIN_SUCCESS;
			}
			return LOGIN_FORBIDDEN;
		}
		it++;
	}
	return LOGIN_EMPTY_ACC;
}

char *handleUpload(ParamInfo *data) {
	if (data->isLogin) return UPLOAD_SUCCESS;
	return UPLOAD_FAIL;
}

char *handleLogout(ParamInfo *data) {
	if (data->isLogin) {
		data->userIndex->isLogin = false;
		data->isLogin = false;
		return LOGOUT_SUCCESS;
	}
	return LOGOUT_FAIL;
}