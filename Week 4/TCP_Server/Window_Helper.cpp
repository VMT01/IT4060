#include "stdafx.h"
#include "Window_Helper.h"
#include "Winsock_Helper.h"
#include "Util.h"

ClientInfo client[MAX_CLIENT];
SOCKET listenSock;

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = windowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_TCP_SERVER));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow) {
	HWND hWnd;
	for (int i = 0; i < MAX_CLIENT; i++) client[i].sock = 0;
	hWnd = CreateWindow(L"WindowClass", L"WSAAsyncSelect TCP Server", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) exit(-1);	// FALSE

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_SOCKET	- process the events on the sockets
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_SOCKET:
			wmSocketCase(hWnd, wParam, lParam);
			break;

		case WM_DESTROY:
			wmDestroyCase();
			break;

		case WM_CLOSE:
			wmCloseCase(hWnd);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void varBridge(void *param) {
	listenSock = (SOCKET)param;
}

void wmSocketCase(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (WSAGETSELECTERROR(lParam)) {
		for (int i = 0; i < MAX_CLIENT; i++) {
			if (client[i].sock == (SOCKET)wParam) {
				closesocket(client[i].sock);
				client[i].sock = 0;
				if (client[i].f != NULL) fclose(client[i].f);
				return;
			}
		}
	}

	switch (WSAGETSELECTEVENT(lParam)) {
		case FD_ACCEPT:
			fdAcceptCase(hWnd, wParam);
			break;

		case FD_READ:
			fdReadCase(wParam);
			break;

		case FD_CLOSE:
			fdCloseCase(wParam);
			break;
	}
}

void wmDestroyCase() {
	PostQuitMessage(0);
	terminate(listenSock);
	exit(0);
}

void wmCloseCase(HWND hWnd) {
	DestroyWindow(hWnd);
	terminate(listenSock);
	exit(0);
}

void fdAcceptCase(HWND hWnd, WPARAM wParam) {
	SOCKET sock;
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr), i;

	sock = accept((SOCKET)wParam, (sockaddr *)&clientAddr, &clientAddrLen);
	if (sock == INVALID_SOCKET) return;

	for (i = 0; i < MAX_CLIENT; i++) {
		if (client[i].sock == 0) {
			client[i].sock = sock;
			//requests Windows message-based notification of network events for listenSock
			WSAAsyncSelect(client[i].sock, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
			break;
		}
	}
	if (i == MAX_CLIENT) MessageBox(hWnd, L"Too many clients!", L"Notice", MB_OK);
}

void fdReadCase(WPARAM wParam) {
	int i;

	for (i = 0; i < MAX_CLIENT; i++) {
		if (client[i].sock == (SOCKET)wParam) break;
	}
	
	handleRequest(client[i]);
}

void fdCloseCase(WPARAM wParam) {
	for (int i = 0; i < MAX_CLIENT; i++) {
		if (client[i].sock == (SOCKET)wParam) {
			closesocket(client[i].sock);
			client[i].sock = 0;
			if (client[i].f != NULL) fclose(client[i].f);
			break;
		}
	}
}