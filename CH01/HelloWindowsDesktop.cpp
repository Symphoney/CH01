// HelloWindowsDesktop.cpp

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("CH01");

// The string that appears in the application's title bar
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR	lpCmdLine,
	_In_ int	nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = 0;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// Store instance handle in global variable
	hInst = hInstance;

	// The parameters to CreateWindowEx explained:
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, // An optional extended window style
		szWindowClass,			// name of the application
		szTitle,				// text that appears in title bar
		WS_OVERLAPPEDWINDOW,	// type of window to create
		CW_USEDEFAULT, CW_USEDEFAULT,		// init position (x, y)
		500, 100,		// init size (width, length)
		NULL,			// parent of this window
		NULL,			// app does not have a menu bar
		hInstance,		// first parameter from WinMain
		NULL			// not used in this application
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained
	ShowWindow(hWnd, // value returned from CreateWindow
		nCmdShow	// fourth parameter from WinMain
	);
	UpdateWindow(hWnd);

	// Main message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

// Function: WndProc(HWND, UINT, WPARAM, LPARAM
//
// Purpose: Processes messages for the main window
//
// WM_PAINT		- Paint the main window
// WM_DESTROY	- post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Just print "Hello, Windows desktop!"
		// in top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End app-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}