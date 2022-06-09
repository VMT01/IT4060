#include "stdafx.h"
#include "TCP_WS_Helper_Server.h"
#include "TCP_Server_Ulti.h"

int main(int argc, char *argv[]) {
	u_short port = getUserInput(argc, argv);
	SOCKET sock;

	/* Start server */
	init(&sock, port);

	/* Start communicate */
	start(sock);

	/* Stop Server */
	terminate(&sock);

    return 0;
}

