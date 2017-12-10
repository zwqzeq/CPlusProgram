#include<windows.h>
#include<tchar.h>
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT WINAPI WndProc(HWND,UINT,UINT,LONG);
HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic);

//主函数
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
long WINAPI WndProc(HWND hWnd,UINT message,UINT wParam,LONG lParam)
{
	HDC hDC;
	HFONT hF;
	PAINTSTRUCT ps; //定义指向包含绘图信息的结构体变量
	wchar_t str[] = L" 你好！欢迎学习VC ";//" Hello VC  ";
	int i = 0;
	static int x[11], y[11];
	static int color[11];
	POINT pt;
	switch(message)  //处理消息
	{
		case WM_CREATE:
			SetTimer(hWnd,1111,200,NULL);
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);	//将屏幕坐标转换为窗口坐标
			for(i = 0; i < 11; i++)
			{
				x[i] = pt.x + (i-1)*40;
				y[i] = pt.y;
				color[i] = 25 * (i-1);
			}
			break;
		case WM_PAINT: //处理重画消息
			hDC=BeginPaint(hWnd,&ps);
			hF = CreateFont(hDC,40,0);
			SelectObject(hDC,hF);
			for(i = 10; i > 1; i--)
			{
				x[i] = x[i-1] + 40;
				y[i] = y[i-1];
			}
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);	//将屏幕坐标转换为窗口坐标

			x[1] = pt.x;
			y[1] = pt.y;
			for(i = 1; i < 11; i++)
			{
				SetTextColor(hDC,RGB(255-color[i],color[i],255));
				TextOutW(hDC,x[i],y[i],&str[i],1);
			}
			color[1] = color[10];
			for(i = 10; i > 1; i--)
				color[i] = color[i-1];
			DeleteObject(hF);
			EndPaint(hWnd,&ps);
			break;
		case WM_TIMER:
			if(wParam==1111)
				InvalidateRect(hWnd, NULL,1);
			break;
		case WM_DESTROY: //处理结束应用程序消息
			KillTimer(hWnd,1);
			PostQuitMessage(0);//结束应用程序
			break;
		default://其他消息处理程序
			return(DefWindowProc(hWnd, message, wParam, lParam)) ;
	}
	return 0;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//定义窗口类
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("窗口示例");
	TCHAR *szTitle = _T("鼠标的应用示例");
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

HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic)
{
	HFONT hFont;
	hFont = CreateFont(
		nCharHeight,
		0,
		0,
		0,
		400,
		bItalic,
		0,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"Arial");
	return hFont;
}