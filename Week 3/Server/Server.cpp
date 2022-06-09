#include "WS_Helper.h"
#include "Util.h"

int main(int argc, char *argv[]) {
	signal(SIGINT, [](int signum) {
		printf("Ctrl C captured - Server will stop immediately\n");
		system("pause");
		exit(signum);
	});

	u_short port = getUserInput(argc, argv);
	SOCKET sock = init(port);
	prepareData();
	start(sock);
	terminate(sock);

    return 0;
}

