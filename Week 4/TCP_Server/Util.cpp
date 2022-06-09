#include "stdafx.h"
#include "Util.h"

void handleRequest(ClientInfo user) {
	char buff[BUFF_SIZE + 7], filename[BUFF_SIZE], *p;
	int ret = recv(user.sock, buff, BUFF_SIZE + 7, 0), key = 0;
	if (ret <= 0) return;
	buff[ret] = 0;

	// get key
	for (int i = 5; i < BUFF_SIZE; i++) {
		if (buff[i] == '|') break;
		key = key * 10 + buff[i] - '0';
	}

	// get file name
	p = strchr(buff, '|') + 1;
	strcpy_s(filename, BUFF_SIZE, p);

	if (buff[0] == '0') encryptRequest(user, key, filename);
	else if (buff[0] == '1') decryptRequest(user, key, filename);
}

void encryptRequest(ClientInfo user, int key, char *filename) {
	time_t timestamp;
	char tempFilename[BUFF_SIZE], buff[BUFF_SIZE + 7], payload[BUFF_SIZE];
	int ret, size;

	// Create new temp file
	time(&timestamp);
	itoa(timestamp, tempFilename, 10);
	strcat_s(tempFilename, BUFF_SIZE, filename);
	user.f = fopen(tempFilename, "wb");

	while (1) {
		ret = recv(user.sock, buff, BUFF_SIZE + 7, 0);
		buff[ret] = 0;
		if (buff[1] == '0' && buff[2] == ' ') {
			send(user.sock, "Receive complete\r\n", 18, 0); 
			break;
		}

		size = 0;
		for (int i = 4; i > 0; i--) {
			if (buff[i] != ' ') size = size * 10 + buff[i] - '0';
		}

		strncpy_s(payload, BUFF_SIZE, &buff[5], size);
		fwrite(payload, 1, size, user.f);
	}
	fclose(user.f);
}

void decryptRequest(ClientInfo user, int key, char *filename) {}

