#pragma once
#include "Header.h"

ATOM				MyRegisterClass(HINSTANCE);
HWND				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	windowProc(HWND, UINT, WPARAM, LPARAM);

void varBridge(void *);

// Window message case
void wmSocketCase(HWND, WPARAM, LPARAM);
void wmDestroyCase();
void wmCloseCase(HWND);

// Socket message case
void fdAcceptCase(HWND, WPARAM);
void fdReadCase(WPARAM);
void fdCloseCase(WPARAM);