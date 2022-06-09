#include "Client_Util.h"
#include "Communicate_Helper.h"

serverInfo getUserInput(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Error: Wrong input format. Try again with Client.exe SERVER_HOST SERVER_PORT\n");
		exit(-1);
	}
	return serverInfo(argv[1], (u_short)strtoul(argv[2], NULL, 0));
}

void start(SOCKET *sock) {
	while (1) {
		system("cls");
		genOption();
		if (handleOption(sock) == true) break;
	}
}

void genOption() {
	printf("* ----------------------------__VMTpld__----------------------------- *\n");
	printf("| Choose your option:                                                 |\n");
	printf("| 1. Login                                                            |\n");
	printf("| 2. Upload post                                                      |\n");
	printf("| 3. Logout                                                           |\n");
	printf("| 0. Exit                                                             |\n");
	printf("| *Small note: Press any key to continue after you choose any options |\n");
	printf("* -----------------------------20194375------------------------------ *\n");
}

bool handleOption(SOCKET *sock) {
	char option, mess[BUFF_SIZE];
	
	printf("Enter your option: ");
	option = _getch();
	system("cls");
	genOption();
	switch (option) {
	case '1':
		printf("Enter your username: ");
		gets_s(mess, BUFF_SIZE);
		sendRequest(sock, LOGIN, mess);
		return false;
	case '2':
		printf("Enter your post: ");
		gets_s(mess, BUFF_SIZE);
		sendRequest(sock, UPLOAD, mess);
		return false;
	case '3':
		sendRequest(sock, LOGOUT, "");
		return false;
	case '0':
		printf("Client will stop immediately\n");
		system("pause");
		return true;
	default:
		return false;
	}
}

void sendRequest(SOCKET *sock, char *method, char *req) {
	char buff[BUFF_SIZE];
	int ret;
	strcpy_s(buff, BUFF_SIZE, "");
	
	strcpy_s(buff, BUFF_SIZE, method);
	strcat_s(buff, BUFF_SIZE, " ");
	strcat_s(buff, BUFF_SIZE, req);
	strcat_s(buff, BUFF_SIZE, ENDING_DELIMITER);

	ret = Send(sock, buff, strlen(buff));
	handleResponse(sock);
}

void handleResponse(SOCKET *sock) {
	char buff[BUFF_SIZE];
	int ret;

	ret = Receive(sock, buff);
	if (ret != SOCKET_ERROR && strlen(buff) > 0) {
		buff[ret] = 0;
		if (strcmp(buff, LOGIN_SUCCESS) == 0) printf("Login successfully");
		else if (strcmp(buff, LOGIN_DUPLICATE) == 0) printf("This account has been logged in another program");
		else if (strcmp(buff, LOGIN_EMPTY_ACC) == 0) printf("Account not found");
		else if (strcmp(buff, LOGIN_FORBIDDEN) == 0) printf("This account has been locked");
		else if (strcmp(buff, UPLOAD_SUCCESS) == 0) printf("Your post has been uploaded successfully");
		else if (strcmp(buff, UPLOAD_FAIL) == 0) printf("You haven't login yet");
		else if (strcmp(buff, LOGOUT_SUCCESS) == 0) printf("Logout successfully");
		else if (strcmp(buff, LOGOUT_FAIL) == 0) printf("You haven't login yet");
		else printf("Cannot login because you have been login with another account");
		_getch();
	}
}