#include "stdafx.h"
#include "UDP_WS_Helper_Server.h"
#include "UDP_Server_Ulti.h"

int main(int argc, char *argv[]) {
	u_short port = getUserInput(argc, argv);
	SOCKET sock;

	/* Start server */
	init(&sock, port);

	/* Start communicate */
	start(sock);

	/* Stop server */
	terminate(&sock);
    return 0;
}

