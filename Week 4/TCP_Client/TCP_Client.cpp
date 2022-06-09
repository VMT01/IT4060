#include "stdafx.h"
#include "Winsock_Helper.h"
#include "Util.h"

int main(int argc, char *argv[]) {
	char host[INET_ADDRSTRLEN] = "127.0.0.1";
	u_short port = 6600;
	
	SOCKET sock = init(host, port);
	start(sock);
	terminate(sock);

    return 0;
}

