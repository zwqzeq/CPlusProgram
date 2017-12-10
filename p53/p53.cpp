#include<windows.h>
#include<stdlib.h>
#include<string.h>
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
HWND hWndMain;

//主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG Message;
	if(!InitWindowsClass(hInstance))
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))
		return FALSE;
	while(GetMessage(&Message,0,0,0))//消息循环
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		return Message.wParam;
}

//消息处理函数
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
		static long nXChar,nCaps,nYChar;
	HDC hDC;   //定义指向设备上下文的句柄	
	HFONT f;
	short x;
    TEXTMETRIC tm;
		short LnCount=8;
		PAINTSTRUCT PtStr; //定义指向包含绘图信息的结构体变量
		static char *textbuf[]=
			{
			"OEM_FIXED_FONT:OEM字符集的固有字体",
			"ANSI_FIXED_FONT:采用windows（ANSI）字符集的等宽字体",
			"ANSI_VAR_FONT:采用windows（ANSI）字符集的不等宽字体",
			"SYSTEM_FONT: 默认字体,屏幕系统字体。这是用于菜单、对话框等等的默认不等宽字体",
			"DEVICE_DEFAULT_FONT:设备使用的默认字体（NT）",
			"DEFAULT_PALETTE:默认调色板",
			"SYSTEM_FIXED_FONT:屏幕系统字体。这是用于菜单、对话框等等的默认等宽字体（在windows 3.0之前使用）",
			"DEFAULT_GUI_FONT:用户界面的默认字体，包括菜单和对话框字体（Windows 95）"
		};
	switch(iMessage)  //处理消息
		{
			case WM_CREATE:	//处理窗口创建消息
				hDC=GetDC(hWnd) ;   //获取当前设备表句柄
				GetTextMetrics(hDC,&tm); //获取字体信息
				nXChar=tm.tmAveCharWidth;  //获取字符宽度
				nYChar=tm.tmHeight+tm.tmExternalLeading;
				nCaps=(tm.tmPitchAndFamily&1?3:2)*nXChar/2;
				ReleaseDC(hWnd,hDC);  //释放当前设备句柄
				return 0;
			case WM_PAINT: //处理重画消息
				hDC=BeginPaint(hWnd,&PtStr); //开始绘画
				for(x=0;x<LnCount;x=x+1)  
				{    //输出文本
					f = (HFONT)GetStockObject(10 + x);
					SelectObject(hDC,f);
					TextOut(hDC,nXChar,50+30*x,textbuf[x],lstrlen(textbuf[x])); 
				}
				EndPaint(hWnd,&PtStr);
				return 0;
			case WM_DESTROY: //结束应用程序
				PostQuitMessage(0);
				return 0;
			default://其他消息处理程序
				return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
		}
}

BOOL InitWindowsClass(HINSTANCE hInstance)//初始化窗口类
{
		WNDCLASS WndClass;
		WndClass.cbClsExtra=0;
		WndClass.cbWndExtra=0;
		WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
		WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
		WndClass.hIcon=LoadIcon(NULL,"END");
		WndClass.hInstance=hInstance;
		WndClass.lpfnWndProc=WndProc;
		WndClass.lpszClassName="WinText";
		WndClass.lpszMenuName=NULL;
		WndClass.style=CS_HREDRAW|CS_VREDRAW;
		return RegisterClass(&WndClass);
}

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow) //初始化窗口
{
	HWND hWnd;
		hWnd=CreateWindow("WinText",  //生成窗口
						"文本显示示例程序",
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
		hWndMain=hWnd;
		ShowWindow(hWnd,nCmdShow);//显示窗口
	 UpdateWindow(hWnd);
		return TRUE;
}
