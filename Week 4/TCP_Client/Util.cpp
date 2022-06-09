#include "stdafx.h"
#include "Util.h"

Input getUserInput(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Error: Wrong input format. Try again with Client.exe SERVER_HOST SERVER_PORT\n");
		exit(-1);
	}
	return { argv[1], (u_short)strtoul(argv[2], NULL, 0) };
}

void start(SOCKET sock) {
	char directory[1024], option[2], key[BUFF_SIZE];
	int size, temp, i, ret;

	while (1) {
		system("cls");
		printf("Enter your directory lead to your file: ");
		gets_s(directory, 1024);
		if (strlen(directory) == 0) break;

		printf("What do you wanna do with this file? (0 - encrypt, 1 - decrypt): ");
		gets_s(option, 2);

		printf("Enter your key: ");
		gets_s(key, BUFF_SIZE);

		if (strcmp(option, "0") == 0) encryptReq(sock, directory, key);
		else decryptReq(sock, directory, key);

		system("pause");
	}
}

void encryptReq(SOCKET sock, char *directory, char *key) {
	char buff[BUFF_SIZE + 7], length[4], payload[BUFF_SIZE], *p;
	int ret, size, temp, i;

	strcpy_s(payload, BUFF_SIZE, key);
	strcat_s(payload, BUFF_SIZE, "|");
	if ((p = strrchr(directory, '\\')) != NULL) {		// Find fix directory file name
		strcat_s(payload, BUFF_SIZE, p + 1);
	} else if ((p = strrchr(directory, '/')) != NULL) { // Find dynamic directory file name
		strcat_s(payload, BUFF_SIZE, p + 1);
	}
	// Now payload have format like [key | file name.file extension]

	// Start encrypt request
	strcpy_s(buff, BUFF_SIZE + 7, "0");					// request method - encrypt
	strncat_s(buff, BUFF_SIZE + 7, "    ", 4);			// size of payload - null
	strcat_s(buff, BUFF_SIZE + 7, payload);				// payload
	strcat_s(buff, BUFF_SIZE + 7, ENDING_DELIMITER);
	// Now buff have format like [0    key|filename.fileextension\r\n]

	send(sock, buff, strlen(buff), 0);

	FILE *f = fopen(directory, "rb");
	if (f == NULL) {
		printf("File corrupted\n");
		send(sock, "3", 1, 0);					// error report
		return;
	}

	while ((size = temp = fread(payload, 1, BUFF_SIZE, f)) > 0) {
		if (size != BUFF_SIZE) payload[size] = 0;

		memset(length, ' ', 4);
		i = 0;
		while (temp) {
			length[i++] = temp % 10 + '0';
			temp /= 10;
		}

		strcpy_s(buff, BUFF_SIZE + 7, "2");
		strncat_s(buff, BUFF_SIZE + 7, length, 4);
		strncat_s(buff, BUFF_SIZE + 7, payload, size);
		strcat_s(buff, BUFF_SIZE + 7, ENDING_DELIMITER);
		send(sock, buff, size + 7, 0);
	}

	// End sending file
	memset(length, ' ', 4);
	length[0] = '0';
	strcpy_s(buff, BUFF_SIZE + 7, "2");
	strncat_s(buff, BUFF_SIZE + 7, length, 4);
	strcat_s(buff, BUFF_SIZE + 7, ENDING_DELIMITER);
	send(sock, buff, strlen(buff), 0);

	ret = recv(sock, buff, BUFF_SIZE + 7, 0);
	if (ret <= 0) printf("Recv error\n");
	else {
		buff[ret] = 0;
		printf("%s\n", buff);
	}
}

void decryptReq(SOCKET sock, char *directory, char *key) {}