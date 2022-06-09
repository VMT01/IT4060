#include "WS_Helper_Client.h"
#include "Client_Util.h"

int main(int argc, char *argv[]) {
	serverInfo svInfo = getUserInput(argc, argv);
	SOCKET sock;

	init(&sock, svInfo.host, svInfo.port);
	start(&sock);
	terminate(&sock);

	return 0;
}