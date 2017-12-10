#include <windows.h>
#include<tchar.h>
#include<math.h>
typedef struct Time
{
	int hour, min, sec;
}TimeStructure;

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AdjustTime(TimeStructure *x);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!InitWindowClass(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"创建窗口失败！", _T("创建窗口"), NULL);
		return 1;
	}
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	HPEN hPen;
	RECT clientRect;
	static TimeStructure x;
	float sita = 0;
	int xOrg, yOrg, rSec, rMin, rHour, rClock, xBegin, xEnd, yBegin, yEnd;
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 9999, 1000, NULL);
		break;
	case WM_PAINT:
		x.sec++;
		AdjustTime(&x);
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &clientRect);
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		hBrush = CreateSolidBrush(RGB(255, 220, 220));
		SelectObject(hDC, hPen);
		SelectObject(hDC, hBrush);
		xOrg = (clientRect.left + clientRect.right) / 2;
		yOrg = (clientRect.top + clientRect.bottom) / 2;
		rClock = min(xOrg, yOrg) - 50;
		rSec = rClock * 6 / 7;
		rMin = rClock * 5 / 6;
		rHour = rClock * 2 / 3;
		Ellipse(hDC, xOrg - rClock, yOrg - rClock, xOrg + rClock, yOrg + rClock);
		for (int i = 0; i<60; i++)
		{
			if (i % 5)
			{
				hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
				SelectObject(hDC, hPen);
				xBegin = xOrg + rClock * sin(2 * 3.1415926 * i / 60);
				yBegin = yOrg + rClock * cos(2 * 3.1415926 * i / 60);
				MoveToEx(hDC, xBegin, yBegin, NULL);
				xEnd = xOrg + (rClock - 20)* sin(2 * 3.1415926 * i / 60);
				yEnd = yOrg + (rClock - 20)* cos(2 * 3.1415926 * i / 60);
			}
			else
			{
				hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
				SelectObject(hDC, hPen);
				xBegin = xOrg + rClock * sin(2 * 3.1415926 * i / 60);
				yBegin = yOrg + rClock * cos(2 * 3.1415926 * i / 60);
				MoveToEx(hDC, xBegin, yBegin, NULL);
				xEnd = xOrg + (rClock - 25)* sin(2 * 3.1415926 * i / 60);
				yEnd = yOrg + (rClock - 25)* cos(2 * 3.1415926 * i / 60);
			}
			LineTo(hDC, xEnd, yEnd);
			DeleteObject(hPen);
		}
		hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		SelectObject(hDC, hPen);
		sita = 2 * 3.1415926 * x.sec / 60;
		xBegin = xOrg + (int)(rSec * sin(sita));
		yBegin = yOrg - (int)(rSec * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.1415926) / 8);
		yEnd = yOrg - (int)(rClock * cos(sita + 3.1415926) / 8);
		MoveToEx(hDC, xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);
		hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		SelectObject(hDC, hPen);
		sita = 2 * 3.1415926 * x.min / 60;
		xBegin = xOrg + (int)(rMin * sin(sita));
		yBegin = yOrg - (int)(rMin * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.1415926) / 8);
		yEnd = yOrg - (int)(rClock * cos(sita + 3.1415926) / 8);
		MoveToEx(hDC, xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);
		hPen = CreatePen(PS_SOLID, 10, RGB(0, 0, 0));
		SelectObject(hDC, hPen);
		sita = 2 * 3.1415926 * x.hour / 12;
		xBegin = xOrg + (int)(rHour * sin(sita));
		yBegin = yOrg - (int)(rHour * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.1415926) / 8);
		yEnd = yOrg - (int)(rClock * cos(sita + 3.1415926) / 8);
		MoveToEx(hDC, xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);
		DeleteObject(hPen);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		if (wParam == 9999)
			InvalidateRect(hWnd, NULL, true);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, true);
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

void AdjustTime(TimeStructure *x)
{
	if (x->sec == 60)
	{
		x->sec = 0;
		x->min++;
		if (x->min == 60)
		{
			x->min = 0;
			x->hour++;
			if (x->hour == 12)
				x->hour = 0;
		}
	}
}
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR szWindowClass[] = L"窗口示例";
	TCHAR szTitle[] = L"模拟时种";
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	if (!RegisterClassEx(&wcex))
		return FALSE;
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}