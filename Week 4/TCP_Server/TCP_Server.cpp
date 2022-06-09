#include "stdafx.h"
#include "Window_Helper.h"
#include "Winsock_Helper.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	HWND window;
	SOCKET sock;

	MyRegisterClass(hInstance);
	if ((window = InitInstance(hInstance, nCmdShow)) == NULL) return FALSE;

	sock = init(window);
	varBridge((void *)sock);
	WSAAsyncSelect(sock, window, WM_SOCKET, FD_ACCEPT | FD_CLOSE | FD_READ);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}