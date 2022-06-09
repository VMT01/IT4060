#pragma once

#define SERVER_ADDR		"127.0.0.1"
#define BUFF_SIZE		2048
#define ENDING_DELIMITER "\r\n"

/* Method */
#define LOGIN			"USER"
#define UPLOAD			"POST"
#define LOGOUT			"BYE"

/* Response */
#define LOGIN_SUCCESS	"10"
#define LOGIN_FORBIDDEN	"11"
#define LOGIN_EMPTY_ACC	"12"
#define LOGIN_DUPLICATE "13"
#define UPLOAD_SUCCESS	"20"
#define UPLOAD_FAIL		"21"
#define LOGOUT_SUCCESS	"30"
#define LOGOUT_FAIL		"21"
#define INVALID_REQUEST "99"