#include "WS_Helper_Server.h"
#include "Server_Util.h"

int main(int argc, char *argv[]) {
	signal(SIGINT, [](int signum) {
		printf("Ctrl C captured - Server will stop immediately\n");
		system("pause");
		exit(signum);
	});
	
	u_short port = getUserInput(argc, argv);
	SOCKET sock;
	vector<Acc> vAcc;

	init(&sock, &port);
	prepareData(&vAcc);
	start(&sock, &vAcc);
	terminate(&sock);

	return 0;
}