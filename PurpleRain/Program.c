#include "includes.h"
#include "PurpleRain.h"

// TODO Make these defines selectable?
#define BG_COLOR RGB(230, 230, 250)
#define FG_COLOR RGB(138, 43, 226)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCommandLine, int nCmdShow);
LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI ThreadProc(LPVOID lpParam);

PurpleRain stPurpleRain;
HBRUSH hbrBg;
HWND hWindow;
BOOL bRunning = TRUE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCommandLine, int nCmdShow)
{
	static TCHAR szWindowClass[] = _T("purpleRain");
	static TCHAR szWindowTitle[] = _T("Purple Rain");

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		return 1;
	}

	RECT rDimens;
	rDimens.top = rDimens.left = 0;
	rDimens.bottom = 480;
	rDimens.right = 640;
	DWORD dwOptsEx = WS_OVERLAPPEDWINDOW;
	if (!AdjustWindowRectEx(&rDimens, WS_CAPTION, FALSE, dwOptsEx))
	{
		return 1;
	}

	CreatePurpleRain(&stPurpleRain, 500, 640, 480, FG_COLOR);

	HANDLE hThread = CreateThread(0, 0, ThreadProc, NULL, 0, NULL);

	hWindow = CreateWindowEx(0, szWindowClass, szWindowTitle, dwOptsEx, CW_USEDEFAULT, CW_USEDEFAULT, rDimens.right - rDimens.left, rDimens.bottom - rDimens.top, NULL, NULL, hInstance, NULL);
	if (!hWindow)
	{
		return 1;
	}

	ShowWindow(hWindow, nCmdShow);
	UpdateWindow(hWindow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	bRunning = FALSE;
	WaitForSingleObject(hThread, INFINITE);

	DestroyPurpleRain(&stPurpleRain);

	return (int)msg.wParam;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rc;
	switch (uMsg)
	{
	case WM_CREATE:
		hbrBg = CreateSolidBrush(BG_COLOR);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, rc.right, rc.bottom, NULL); // TODO Investigate using our own coordinate system
		SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
		FillRect(hdc, &rc, hbrBg);
		
		for (int i = 0; i < stPurpleRain.Count; i++)
		{
			PDrop d = GetDrop(&stPurpleRain, i);
			if (d != NULL)
			{
				float thick = DropGetThickness(d);
				//HPEN pen = ExCreatePen(PS_SOLID, (int)thick, FG_COLOR);
				LOGBRUSH lbFgBrush;
				lbFgBrush.lbColor = FG_COLOR;
				lbFgBrush.lbStyle = BS_SOLID;
				lbFgBrush.lbHatch = 0;
				HPEN pen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_ROUND, (int)thick, &lbFgBrush, 0, NULL);
				SelectObject(hdc, pen);
				MoveToEx(hdc, (int)d->X, (int)d->Y, NULL);
				LineTo(hdc,(int)d->X, (int)(d->Y + d->Len));
				DeleteObject(pen);
			}
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	while (bRunning)
	{
		AnimatePurpleRain(&stPurpleRain);
		InvalidateRect(hWindow, NULL, TRUE);
		Sleep(30);
	}
	return 0;
}
