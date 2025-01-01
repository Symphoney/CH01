// HelloWindowsDesktop.cpp

#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <VersionHelpers.h>
#include "Resource.h"

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("CH01");

// The string that appears in the application's title bar
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Constants for animation
#define TIMER_ID 1
#define TIMER_INTERVAL 200 // 200 ms

// Global variables for animation
TCHAR fullGreeting[256];
TCHAR animatedText[256];
int charIndex = 0;


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
	// wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CUSTOM_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_HAND);
	wcex.hbrBackground = CreateSolidBrush(RGB(135, 206, 235)); // sky blue
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
		400, 150,		// init size (width, length)
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
	static HWND hButton; // Store button handle
	

	PAINTSTRUCT ps;
	HDC hdc;

	

	switch (message)
	{
	case WM_CREATE:
	{
		// Create button when window is created
		hButton = CreateWindow(
			_T("BUTTON"), _T("Click Me"),
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			50, 50, 100, 30,
			hWnd, (HMENU)1, hInst, NULL);

		// Init full greeting message
		SYSTEMTIME st;
		GetLocalTime(&st);
		HMENU hMenu = CreateMenu();
		AppendMenu(hMenu, MF_STRING, 1, _T("Exit"));
		SetMenu(hWnd, hMenu);

		if (st.wHour < 12)
			_tcscpy_s(fullGreeting, _T("Good morning, rija!"));
		else if (st.wHour < 18)
			_tcscpy_s(fullGreeting, _T("Good afternoon, rija!"));
		else
			_tcscpy_s(fullGreeting, _T("Good evening, rija!"));

		// Start timer for animation
		SetTimer(hWnd, TIMER_ID, TIMER_INTERVAL, NULL);
		charIndex = 0;
		animatedText[0] = '\0';
	}
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == 1)
		{
			if ((HWND)lParam == hButton)
			{
				// Button clicked
				MessageBox(hWnd, _T("button says hi!"), _T("u clicked on me!"), MB_OK);
			}
			else {
				// Exit menu item selected
				PostQuitMessage(0);
			}
		}

	case WM_TIMER:
		if (wParam == TIMER_ID)
		{
			// Update animated text
			if (charIndex < _tcslen(fullGreeting))
			{
				animatedText[charIndex] = fullGreeting[charIndex];
				animatedText[charIndex + 1] = '\0';
				charIndex++;
				InvalidateRect(hWnd, NULL, TRUE); // Request a repaint
			}
		}
		break;


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Draw greeting message
		TextOut(hdc, 5, 5, animatedText, _tcslen(animatedText));

		// Fetch and display system information
		TCHAR sysInfo[256];

		// Use VersionHelpers to check the version
		if (IsWindows10OrGreater())
		{
			_stprintf_s(sysInfo, _T("Windows Version: 10 or Greater"));
		}
		else if (IsWindows8OrGreater())
		{
			_stprintf_s(sysInfo, _T("Windows Version: 8 or Greater"));
		}
		else if (IsWindows7OrGreater())
		{
			_stprintf_s(sysInfo, _T("Windows Version: 7 or Greater"));
		}
		else
		{
			_stprintf_s(sysInfo, _T("Older Windows Version"));
		}

		TextOut(hdc, 5, 30, sysInfo, _tcslen(sysInfo));

		EndPaint(hWnd, &ps);
		break;


	// Interactive Keyboard Input
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			MessageBox(hWnd, _T("You pressed Enter!"), _T("Key Press"), MB_OK);
		}
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