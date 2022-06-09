#pragma once

#define BUFF_SIZE 2048
#define TIME_INTERVAL 10000
#define ENDING_DELIMITER "\r\n"

/* Method */
#define LOGIN			"USER"
#define UPLOAD			"POST"
#define LOGOUT			"BYE"

/* Response */
#define LOGIN_SUCCESS	"10\r\n"
#define LOGIN_FORBIDDEN	"11\r\n"
#define LOGIN_EMPTY_ACC	"12\r\n"
#define LOGIN_DUPLICATE "13\r\n"
#define UPLOAD_SUCCESS	"20\r\n"
#define UPLOAD_FAIL		"21\r\n"
#define LOGOUT_SUCCESS	"30\r\n"
#define LOGOUT_FAIL		"21\r\n"
#define INVALID_REQUEST "99\r\n"