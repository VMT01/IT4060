#include "stdafx.h"
#include "TCP_WS_Helper_Client.h"
#include "TCP_Client_Ulti.h"

int main(int argc, char *argv[]) {
	serverInfo svInfo = getUserInput(argc, argv);
	SOCKET sock;

	/* Start client */
	init(&sock, svInfo.host, svInfo.port);

	/* Start communicate */
	start(sock);

	/* Stop client */
	terminate(&sock);

	return 0;
}