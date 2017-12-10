#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"resource.h"
void WINAPI CaretPos(HWND hWnd,int nArrayPos,char *cCharBuf,int *xCaret,int *yCaret,int nCharWidth);
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
HWND hWndMain;
HINSTANCE hinst;
//主函数
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	hinst = hInstance;
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
	WORD x,y;         		//定义表示坐标的变量
	HCURSOR hCursor;  		//定义表示鼠标的变量
	char s[80];
	switch(iMessage)  		//消息处理
	{
//	case WM_NCHITTEST:
//		return (LRESULT) HTCAPTION ;
	case WM_LBUTTONDOWN:
		sprintf(s,"%d",wParam);
		MessageBox(0,s,"",0);
		break;
	case WM_NCLBUTTONDBLCLK:
		MessageBox(0,"a","",0);
		if(wParam==HTSYSMENU)
			return 0;
		break;
	case WM_MOUSEMOVE:   	//处理鼠标移动消息
		x=LOWORD(lParam); //取得鼠标所在位置在工作区中的坐标值
		y=HIWORD(lParam);
	//当在左上角为(50,50)，右下角为(400,300)确定的矩形区域中时，该变鼠标的形状
		if(x>=50&&x<=400&&y>=50&&y<=300)  
		{
			if(x>=50&&x<=100&&y>=50&&y<=100)
			{
				hCursor=LoadCursor(NULL,IDC_CROSS); //定义一个"十"字型鼠标
				SetCursor(hCursor);//设置当前鼠标为上句中定义的"十"字型鼠标
			}
			if(x>=100&&x<=150&&y>=50&&y<=100)
			{
				hCursor=LoadCursor(NULL,IDC_SIZE); //定义一个双箭头型鼠标
				SetCursor(hCursor);	//设置当前鼠标为上句中定义的双箭头型鼠标
			}
			if(x>=150&&x<=200&&y>=50&&y<=100)
			{
				hCursor=LoadCursor(NULL,IDC_SIZE); //定义一个双箭头型鼠标
				SetCursor(hCursor);	//设置当前鼠标为上句中定义的双箭头型鼠标
			}
			if(x>=50&&x<=100&&y>=100&&y<=150)
			{
				//定义一个用于该变窗体对角线大小的双箭头型鼠标
				hCursor=LoadCursor(NULL,IDC_SIZENESW);
				SetCursor(hCursor);//设置当前鼠标为上句中定义的鼠标
			}
			if(x>=100&&x<=250&&y>=100&&y<=150)
			{
				//定义鼠标为改变上下大小的双箭头型鼠标
				hCursor=LoadCursor(NULL,IDC_SIZENS); 
				SetCursor(hCursor);
			}
			if(x>=250&&x<=400&&y>=100&&y<=150)
			{
				//定义一个用于该变窗体对角线大小的双箭头型鼠标
				hCursor=LoadCursor(NULL,IDC_SIZENWSE); 
				SetCursor(hCursor);
			}
			if(x>=50&&x<=100&&y>=150&&y<=300)
			{
				//定义一个用于该变窗体左右方向上大小的双箭头型鼠标
				hCursor=LoadCursor(NULL,IDC_SIZEWE);
				SetCursor(hCursor);
			}
			if(x>=100&&x<=250&&y>=150&&y<=300)
			{
				//定义一个方向向上的箭头型鼠标
				hCursor=LoadCursor(NULL,IDC_UPARROW);
				SetCursor(hCursor);
			}
			if(x>=250&&x<=400&&y>=150&&y<=300)
			{	//设置一个用于表示系统忙的鼠标
				hCursor=LoadCursor(NULL,IDC_WAIT);
				SetCursor(hCursor);
			}
		}
		else
		{
			hCursor=LoadCursor(hinst,(LPCTSTR)IDC_CURSOR1);//IDC_ARROW);  //其他区域设置成普通的箭头型鼠标
			SetCursor(hCursor);
		}
		return 0;
	case WM_DESTROY: //处理结束应用程序消息
		PostQuitMessage(0);//结束应用程序
		return 0;
	default://其他消息处理程序
		return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
	}
}

BOOL InitWindowsClass(HINSTANCE hInstance) //初始化窗口类
{
	WNDCLASS WndClass;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,"END");
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName="WinMouse";
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW|CS_VREDRAW;
	return RegisterClass(&WndClass);
}

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow) //初始化窗口
{
	HWND hWnd;
	hWnd=CreateWindow("WinMouse",  //生成窗口
					"鼠标及光标形状设置示例",
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
