#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
HWND hWndMain;
int i = 0;
static char str[200][80];
LOGFONT lf;

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

int StrSearch(int num,char *s)
{
	for(int k=0;k<num;k++)
		if(strcmp(str[k],s)==0)
			return 1;
	return 0;
}

int CALLBACK EnumFontFamProc(
	 ENUMLOGFONT *lpelf,	//指向ENUMLOGFONT结构体指针
	 NEWTEXTMETRIC *lpntm,	//指向NEWTEXTMETRIC结构体指针
	int type,		//字体类型
	LPARAM lParam)
{
	char s[80];
	strcpy(s,(char*)lpelf->elfFullName);
	int search;
	search = StrSearch(i,s);
	if( !search)
		strcpy(str[i++],(char*)lpelf->elfFullName);
	if(i==1)
		lf = lpelf->elfLogFont;
	if (i<200)
		return 1;
	else
		return 0;
}
//消息处理函数
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	static long nXChar,nCaps,nYChar;
	HDC hDC;   //定义指向设备上下文的句柄	
	HFONT f,oldf;
    TEXTMETRIC tm;
	LOGFONT LogFont;
	PAINTSTRUCT PtStr; //定义指向包含绘图信息的结构体变量
	int k;
	memset(&LogFont,0,sizeof(LogFont));
	LogFont.lfCharSet = GB2312_CHARSET;//DEFAULT_CHARSET;
//	strcpy(LogFont.lfFaceName,"Arial");
	LogFont.lfFaceName[0]=0;
	LogFont.lfPitchAndFamily = 0;
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
			case WM_LBUTTONDOWN:

				hDC = GetDC(hWnd);
				EnumFontFamiliesEx((HDC)hDC,&LogFont,(FONTENUMPROC)EnumFontFamProc,(LPARAM)0,0);
				ReleaseDC(hWnd,hDC);
				InvalidateRect(hWnd,NULL,1);				//刷新用户区
				break;
			case WM_PAINT: //处理重画消息
				hDC=BeginPaint(hWnd,&PtStr); //开始绘画
				for(k=0;k<30;k++)
				{
					strcpy(lf.lfFaceName,str[k]);
					f = CreateFontIndirect(&lf);
					oldf = (HFONT)SelectObject(hDC,f);
					TextOut(hDC,10,10+22*k,str[k],strlen(str[k]));
					SelectObject(hDC,oldf);
					DeleteObject(f);
				}
				for(k=30;k<60&&k<i;k++)
				{
					strcpy(lf.lfFaceName,str[k]);
					f = CreateFontIndirect(&lf);
					oldf = (HFONT)SelectObject(hDC,f);
					TextOut(hDC,200,10+22*(k-30),str[k],strlen(str[k]));
					SelectObject(hDC,oldf);
					DeleteObject(f);
				}
				for(k=60;k<90&&k<i;k++)
				{
					strcpy(lf.lfFaceName,str[k]);
					f = CreateFontIndirect(&lf);
					oldf = (HFONT)SelectObject(hDC,f);
					TextOut(hDC,400,10+22*(k-60),str[k],strlen(str[k]));
					SelectObject(hDC,oldf);
					DeleteObject(f);
				}
				for(k=90;k<i&&k<120;k++)
				{
					strcpy(lf.lfFaceName,str[k]);
					f = CreateFontIndirect(&lf);
					oldf = (HFONT)SelectObject(hDC,f);
					TextOut(hDC,600,10+22*(k-90),str[k],strlen(str[k]));
					SelectObject(hDC,oldf);
					DeleteObject(f);
				}
				for(k=120;k<i&&k<150;k++)
				{
					strcpy(lf.lfFaceName,str[k]);
					f = CreateFontIndirect(&lf);
					oldf = (HFONT)SelectObject(hDC,f);
					TextOut(hDC,800,10+25*(k-120),str[k],strlen(str[k]));
					SelectObject(hDC,oldf);
					DeleteObject(f);
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
