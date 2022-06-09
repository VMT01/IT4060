#include "Util.h"
#include "Communicate_Helper.h"
#include "APIs.h"

vector<GlobalInfo> vClientInfo;
vector<Acc> vAcc;
const int maxSize = FD_SETSIZE - 1;

/**
* Prepare data from account.txt and store in RAM
* @return none
*/
void prepareData() {
	FILE *f = fopen("./account.txt", "r");
	if (NULL == f) {
		printf("File corrupted\n");
		exit(-1);
	}

	char str[255];
	int index;

	while (fgets(str, 255, f)) {
		index = strchr(str, ' ') - str;
		char *username = (char *)malloc((index + 1) * sizeof(char));
		strncpy_s(username, index + 1, str, index);
		vAcc.push_back({ username, str[index + 1] });
	}

	fclose(f);
}

/**
* Get user input from terminal
* @param argc: argument count
* @param argv: argument value array
* @return server port number
*/
u_short getUserInput(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Error: Wrong input format. Try again with Server.exe SERVER_PORT\n");
		exit(-1);
	}
	return (u_short)strtoul(argv[1], NULL, 0);
}

/**
* Start the magic, atleast for me :D
* @param sock: Socket number
* @return none
*/
void start(SOCKET sock) {
	sockaddr_in clientAddr;
	char clientIP[INET_ADDRSTRLEN];
	int clientAddrLen = sizeof(clientAddr);
	u_short clientPort;
	HANDLE hThread;
	SOCKET connSock;

	while (1) {
		connSock = accept(sock, (sockaddr *)&clientAddr, &clientAddrLen);
		if (connSock == SOCKET_ERROR) {
			printf("Error %d: Cannot permit incoming connection\n", WSAGetLastError());
		}
		else {
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
			clientPort = ntohs(clientAddr.sin_port);
			printf("Accept incoming connection from %s:%d\n", clientIP, clientPort);

			NewClientConnectInfo res = handleNewConnection(connSock, clientIP, clientPort);

			switch (res.flag) {
			case CLIENT_ASSIGN_AT_FIRST_INDEX:
				hThread = (HANDLE)_beginthreadex(0, 0, communicate, (void *)new ThreadInfo(sock, res.offset), 0, 0);
				break;
			case CLIENT_ASSIGN_AT_EMPTY_INDEX:
				break;
			case CLIENT_OUT_OF_BOUND:
				// Create new over here
				vClientInfo.push_back({
					{ connSock, clientIP, clientPort },
					1
				});
				hThread = (HANDLE)_beginthreadex(0, 0, communicate, (void *)new ThreadInfo(sock, res.offset), 0, 0);
				break;
			default:
				break;
			}
		}
	}
	WaitForSingleObject(hThread, INFINITE);
}

/**
* Handle new connection into vector client info
* @param connSock: User socket number
* @param clientIP: Client host address
* @param clientPort: Client port number
* @return create new thread flag and index of user in vector client info
*/
NewClientConnectInfo handleNewConnection(SOCKET connSock, char *clientIP, u_short clientPort) {
	flags flag;
	flag = CLIENT_OUT_OF_BOUND;
	int i;
	for (i = 0; i < vClientInfo.size(); i++) {
		// If there is no client in set, let assign this new client into first slot
		if (vClientInfo[i].clientCount == 0) {
			vClientInfo[i].client[0] = { connSock, clientIP, clientPort };
			vClientInfo[i].clientCount++;
			flag = CLIENT_ASSIGN_AT_FIRST_INDEX;
			break;
		}
		// If there is a slot, let assign this client into this slot
		else if (vClientInfo[i].clientCount < maxSize) {
			for (int j = 0; j < maxSize; j++) {
				if (vClientInfo[i].client[j].sock == 0) {
					vClientInfo[i].client[j] = { connSock, clientIP, clientPort };
					vClientInfo[i].clientCount++;
					break;
				}
			}
			flag = CLIENT_ASSIGN_AT_EMPTY_INDEX;
			break;
		}
	}

	// If there no slot, must create new thread then
	return { flag, i }; 
}

/**
* Start the thread for a set of client
* @param param: A pointer to thread parameter
* @return default 0
*/
unsigned __stdcall communicate(void *param) {
	printf("Create thread at %ld\n", _threadid);

	ThreadInfo *data = (ThreadInfo *)param;
	fd_set readfds;
	int ret, nEvents;
	char buff[BUFF_SIZE];
	timeval tv = { 0, 10000 };

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(data->sock, &readfds);
		for (int i = 0; i < maxSize; i++) {
			if (vClientInfo[data->offset].client[i].sock != 0) {
				FD_SET(vClientInfo[data->offset].client[i].sock, &readfds);
			}
		}
		nEvents = select(0, &readfds, 0, 0, &tv);

		if (nEvents < 0) {
			printf("Error! Cannot poll sockets: %d\n", WSAGetLastError());
			break;
		}
		if (nEvents == 0) {
			if (vClientInfo[data->offset].clientCount == 0) break;
			continue;
		}

		// Receive data from clients
		for (int i = 0; i < maxSize; i++) {
			if (vClientInfo[data->offset].client[i].sock == 0) continue;
			if (FD_ISSET(vClientInfo[data->offset].client[i].sock, &readfds)) {
				ret = Receive(vClientInfo[data->offset].client[i], buff);
				if (ret <= 0) {
					FD_CLR(vClientInfo[data->offset].client[i].sock, &readfds);
					closesocket(vClientInfo[data->offset].client[i].sock);
					if (vClientInfo[data->offset].client[i].isLogin) {
						vClientInfo[data->offset].client[i].userIndex->isLogin = false;
						vClientInfo[data->offset].client[i].isLogin = false;
					}
					vClientInfo[data->offset].client[i] = {};
					vClientInfo[data->offset].clientCount--;
				} else if (ret > 0) {
					buff[ret] = 0;
					strcat_s(vClientInfo[data->offset].client[i].messQueue, BUFF_SIZE, buff);
					printf("[%s:%d] %s\n", vClientInfo[data->offset].client[i].clientIP, vClientInfo[data->offset].client[i].clientPort, vClientInfo[data->offset].client[i].messQueue);
					
					processData(&vClientInfo[data->offset].client[i]);
				}
			}
			if (--nEvents <= 0) continue;
		}
	}

	printf("End thread %d\n", _threadid);
	return 0;
}

/**
* @function processData: Handle bytestream message and send response to client
* @param data: A pointer to thread parameter
* @return none
*/
void processData(ClientInfo *data) {
	int index, messQueueLen;
	char *p, buff[BUFF_SIZE], token[BUFF_SIZE];

	while ((p = strstr(data->messQueue, ENDING_DELIMITER)) != NULL) {
		index = p - data->messQueue;
		messQueueLen = strlen(data->messQueue);
		strncpy_s(token, BUFF_SIZE, data->messQueue, index);
		strncpy_s(data->messQueue, BUFF_SIZE, &data->messQueue[index + 2], messQueueLen - index - 2);

		strcpy_s(buff, BUFF_SIZE, handleMessage(data, token));
		strcat_s(buff, BUFF_SIZE, ENDING_DELIMITER);
		Send(*data, buff, strlen(buff));
	}
}

/**
* Handle single user request
* @param data: A pointer to thread parameter
* @param token: A request of user get from messQueue bytestream
* @return: Server response code
*/
char *handleMessage(ClientInfo *data, char *token) {
	char *p, value[BUFF_SIZE];
	int len = strlen(token), methodLen;

	if ((p = strstr(token, LOGIN)) == token) {
		methodLen = strlen(LOGIN) + 1;
		strncpy_s(value, BUFF_SIZE, &token[methodLen], len - methodLen);
		return handleLogin(data, value, &vAcc);
	} else if ((p = strstr(token, UPLOAD)) == token) {
		methodLen = strlen(UPLOAD) + 1;
		strncpy_s(value, BUFF_SIZE, &token[methodLen], len - methodLen);
		return handleUpload(data);
	} else if ((p = strstr(token, LOGOUT)) == token) {
		return handleLogout(data);
	}

	return INVALID_REQUEST;
}