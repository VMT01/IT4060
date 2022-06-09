#include "stdafx.h"
#include "UDP_WS_Helper_Client.h"
#include "UDP_Client_Ulti.h"

int main(int argc, char *argv[]) {
	serverInfo svInfo = getUserInput(argc, argv);
	SOCKET sock;

	/* Start client */
	init(&sock);

	/* Start communication */
	start(sock, svInfo);

	/* Stop client */
	terminate(&sock);
    return 0;
}

