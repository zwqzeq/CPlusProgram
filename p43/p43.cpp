#include<windows.h>
#include<tchar.h>
#include<math.h>
typedef struct Time
{
	int hour, minute, second;
}TimeStructure;
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AdjustTime(TimeStructure *x);
//主函数
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	if(!InitWindowClass(hInstance, nCmdShow))
	{
		MessageBox(NULL, _T("创建窗口失败！"), _T("创建窗口"),NULL);
		return 1;
	}
	while(GetMessage(&Message,0,0,0))	//消息循环
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//消息处理函数 
LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,UINT wParam,LONG lParam)
{
	HDC hDC;   			//定义指向设备上下文的句柄
	PAINTSTRUCT ps; 	//定义指向包含绘图信息的结构体变量
	static HBRUSH hBrush, hOldBrush;  		//定义指向画刷的句柄
	static HPEN hPenSecond, hPenMinute, hPenHour, hPenRed, hOldPen,hPen;	//定义指向画笔的句柄
	RECT clientRect;
	static TimeStructure x;
	float sita = 0;
	int xOrg, yOrg, rSec, rMin, rHour, rClock, xBegin,yBegin,xEnd,yEnd, i;
	switch(Message)  //处理消息
	{
	case WM_CREATE:
		hBrush = CreateSolidBrush(RGB(255,220,220));//粉红色
		hPenSecond = CreatePen(PS_SOLID, 2, RGB(255,0,0));
		hPenMinute = CreatePen(PS_SOLID, 5, RGB(0,0,0));
		hPenHour = CreatePen(PS_SOLID, 10, RGB(0,0,0));
		SetTimer(hWnd, 9999,1000,NULL);
		hPenRed = CreatePen(PS_SOLID, 5, RGB(255,0,0));
		break;
	case WM_PAINT:    							//处理绘图消息
//		x.second++;
		AdjustTime(&x);
		hDC=BeginPaint(hWnd,&ps);
		GetClientRect(hWnd, &clientRect);
		hPen=(HPEN)GetStockObject(BLACK_PEN);//设置画笔为系统预定定义的黑色画笔
		hOldPen = (HPEN)SelectObject(hDC,hPen);    			//选择画笔
		hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		xOrg = (clientRect.left + clientRect.right)/2;
		yOrg = (clientRect.top + clientRect.bottom)/2;

		rClock = min(xOrg, yOrg) - 50;
		rSec = rClock * 6 / 7;
		rMin = rClock * 5 / 6;
		rHour = rClock * 2 / 3;
		Ellipse(hDC, xOrg - rClock, yOrg - rClock, xOrg + rClock, yOrg + rClock);
		DeleteObject(hPen);	//

		for(i=0; i<60; i++)
		{
			if(i%5)
			{
				SelectObject(hDC, hPenSecond);
				xBegin = xOrg + rClock*sin(2*3.14159*i/60);
				yBegin = yOrg + rClock*cos(2*3.14159*i/60);
				xEnd = xOrg + (rClock-20)*sin(2*3.14159*i/60);
				yEnd = yOrg + (rClock-20)*cos(2*3.14159*i/60);
			}
			else
			{
//				hPen = CreatePen(PS_SOLID, 5, RGB(255,0,0));
				SelectObject(hDC, hPenRed);
				xBegin = xOrg + rClock*sin(2*3.14159*i/60);
				yBegin = yOrg + rClock*cos(2*3.14159*i/60);
				xEnd = xOrg + (rClock-25)*sin(2*3.14159*i/60);
				yEnd = yOrg + (rClock-25)*cos(2*3.14159*i/60);
			}
			MoveToEx(hDC, xBegin, yBegin, NULL);
			LineTo(hDC, xEnd, yEnd);
		}

		sita = 2*3.14159*x.second/60;
		xBegin = xOrg + (int)(rSec * sin(sita));
		yBegin = yOrg - (int)(rSec * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.14159)/8);//sin(π+θ)
		yEnd = yOrg - (int)(rClock * cos(sita + 3.14159)/8);
		DeleteObject(hPen);	//
//		hPen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
		SelectObject(hDC, hPenSecond);
		MoveToEx(hDC,xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);

		sita = 2*3.14159*x.minute/60;
		xBegin = xOrg + (int)(rMin * sin(sita));
		yBegin = yOrg - (int)(rMin * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.14159)/8);//sin(π+θ)
		yEnd = yOrg - (int)(rClock * cos(sita + 3.14159)/8);
		DeleteObject(hPen);	//
//		hPen = CreatePen(PS_SOLID, 5, RGB(0,0,0));
		SelectObject(hDC, hPenMinute);
		MoveToEx(hDC,xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);
		
		sita = 2*3.14159*x.hour/12;
		xBegin = xOrg + (int)(rHour * sin(sita));
		yBegin = yOrg - (int)(rHour * cos(sita));
		xEnd = xOrg + (int)(rClock * sin(sita + 3.14159)/8);//sin(π+θ)
		yEnd = yOrg - (int)(rClock * cos(sita + 3.14159)/8);
		DeleteObject(hPen);	//
//		hPen = CreatePen(PS_SOLID, 10, RGB(0,0,0));
		SelectObject(hDC, hPenHour);
		MoveToEx(hDC,xBegin, yBegin, NULL);
		LineTo(hDC, xEnd, yEnd);

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);
		EndPaint(hWnd,&ps);  				//结束绘图
		break;
	case WM_TIMER:
		if(wParam == 9999)
			InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY: 						//结束应用程序
		DeleteObject(hPenRed);
		DeleteObject(hPenSecond);
		DeleteObject(hPenMinute);
		DeleteObject(hPenHour);
		DeleteObject(hPen);
		DeleteObject(hBrush);

		PostQuitMessage(0);
		return 0;
	default:									//其他消息处理程序
		return(DefWindowProc(hWnd, Message,wParam,lParam)) ;
		break;
	}
	return 0;
}
 
void AdjustTime(TimeStructure *x)
{
/*	if(x->second==60)
	{
		x->second = 0;
		x->minute++;
		if(x->minute==60)
		{
			x->minute = 0;
			x->hour++;
			if(x->hour==12)
				x->hour=0;
		}
	}*/
	SYSTEMTIME st;
	GetLocalTime(&st);
	x->hour = (st.wHour)%12;
	x->minute = st.wMinute;
	x->second = st.wSecond;
	
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//定义窗口类
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("窗口示例");
	TCHAR *szTitle = _T("模拟时钟");
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;						//窗口类型为缺省类型
	wcex.lpfnWndProc = WndProc ;		//窗口处理函数为WndProc
	wcex.cbClsExtra	= 0 ;				//窗口类无扩展
	wcex.cbWndExtra	= 0 ;				//窗口实例无扩展
	wcex.hInstance = hInstance ;		//当前实例句柄
	wcex.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_APPLICATION) ) ;
											//窗口的最小化图标为缺省图标
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW) ;
											//窗口采用箭头光标
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH) ;
											//窗口背景为白色
	wcex.lpszMenuName = NULL ;			//窗口中无菜单
	wcex.lpszClassName = szWindowClass ;//窗口类名为"窗口示例"
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION) ) ;
	if( !RegisterClassEx( &wcex))		//如果注册失败则返回
		return FALSE ;
	hWnd=CreateWindow(szWindowClass,  						//生成窗口
						szTitle,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						0,
						CW_USEDEFAULT,
						0,
						NULL,
						NULL,
						hInstance,
						NULL);
	if(!hWnd)
			return FALSE;
	ShowWindow(hWnd,nCmdShow);					//显示窗口
	UpdateWindow(hWnd);
	return TRUE;
}
