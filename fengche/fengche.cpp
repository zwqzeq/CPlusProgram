#include <windows.h>
#include<stdio.h>
#define DIVISIONS 5
#include <math.h>
#define Pi 3.1415926
#define R 50		//风车半径
#define NUM 3		//子窗口个数
int nMaxNum = 20;	//nMaxNum记录了叶片循环一周中绘图的次数.

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM) ;
TCHAR szChildClass[] = TEXT ("ChildWindow") ;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Checker3") ;
	HWND hwnd ;
	MSG msg ;
	WNDCLASS wndclass ;
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc = WndProc ;
	wndclass.cbClsExtra = 0 ;
	wndclass.cbWndExtra = 0 ;
	wndclass.hInstance = hInstance ;
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,0));//(HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName = NULL ;
	wndclass.lpszClassName = szAppName ;
	if (!RegisterClass (&wndclass))
	{
		MessageBox ( NULL, TEXT ("Program requires Windows NT!"),szAppName, MB_ICONERROR) ;
		return 0 ;
	}
	wndclass.lpfnWndProc = ChildWndProc ;
	wndclass.cbWndExtra = 2*sizeof (long) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (NULL_BRUSH) ;//设子窗口的背景为透明
	wndclass.lpszClassName = szChildClass ;
	RegisterClass (&wndclass) ;						//注册子窗口类型
	hwnd = CreateWindow (szAppName, TEXT ("主窗口与子窗口"),
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT,
							CW_USEDEFAULT, CW_USEDEFAULT,
							NULL, NULL, hInstance, NULL) ;
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}
	return msg.wParam ;
}

//主窗口消息处理函数.
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
{
	static HWND hwndChild[NUM] ;
	static int cxBlock, cyBlock;
	static POINT ps;
	int i;
	switch (message)
	{
	case WM_CREATE :
		for( i = 0; i < NUM; i++)
		{
			hwndChild[i] = CreateWindow (szChildClass, NULL,
				WS_CHILDWINDOW | WS_VISIBLE/* | WS_SYSMENU| WS_CAPTION*/ ,
				0, 0, 0, 0,
				hwnd, (HMENU)i,					//子窗口的ID值
				(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
				NULL) ;
			SetWindowLong(hwndChild[i],0,i);	//设定窗口第一个附加信息－窗口序号
			SetWindowLong(hwndChild[i],4,0);	//设定窗口第二个附加信息－窗口风车转动次数
			SetTimer(hwndChild[i],i,(i+1)*30,0);
		}
		return 0 ;
	case WM_SIZE :	//将子窗口按合适的尺寸和位置置于主窗口中
		cxBlock = LOWORD (lParam) / 2 ;
		cyBlock = HIWORD (lParam) / 2 ;
		for( i=0; i<NUM;i++)
			MoveWindow ( hwndChild[i],R+i*(2*R+20), cyBlock-R,2*R, 2*R, TRUE) ;
		return 0 ;
	case WM_LBUTTONDOWN :
		MessageBeep (0) ;
		return 0 ;
	case WM_DESTROY :
		PostQuitMessage (0) ;
		return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}

//子窗口消息处理函数.
long WINAPI ChildWndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	HDC hDC;				//定义设备环境句柄.
	HBRUSH hBrush;			//定义画刷句柄
	HPEN hPen;				//定义画笔句柄
	PAINTSTRUCT PtStr;		//定义包含绘图信息的结构体变量
	int nCentreX,nCentreY;	//定义3个叶片的圆心的坐标.
	int nNum;				//当前的序数.
	double fAngle;

	switch(iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		KillTimer(hWnd,GetWindowLong(hWnd,0));
		break;
	case WM_PAINT:							//处理绘图消息.
		nNum = GetWindowLong (hWnd, 4);
		hDC=BeginPaint(hWnd,&PtStr);		//获得设备环境指针.
		SetMapMode(hDC,MM_ANISOTROPIC);		//设置映射模式.
		SetViewportOrgEx(hDC,R,R,NULL);	//设置视口原点坐标为(300,200).物理单位.
		//绘制外圆。
		hPen = (HPEN)GetStockObject(BLACK_PEN);
		SelectObject(hDC,hPen);
		Ellipse(hDC,-R,-R,R,R);
		//绘制风车的叶片。

		hBrush = CreateSolidBrush(RGB(255,0,0));		//画红色的叶片.
		SelectObject(hDC,hBrush);
		fAngle = 2*Pi/nMaxNum*nNum;						//计算叶片角度
		nCentreX = (int)(R/2*cos(fAngle));
		nCentreY = (int)(R/2*sin(fAngle));
		Pie(hDC,nCentreX-R/2,nCentreY-R/2,
			nCentreX+R/2,nCentreY+R/2,
			(int)(nCentreX+R/2*cos(fAngle)),(int)(nCentreY+R/2*sin(fAngle)),
			(int)(nCentreX+R/2*cos(fAngle+Pi)),(int)(nCentreY+R/2*sin(fAngle+Pi)));

		hBrush = CreateSolidBrush(RGB(255,255,0));		//画天蓝色的叶片.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(R/2*cos(fAngle+2*Pi/3));
		nCentreY = (int)(R/2*sin(fAngle+2*Pi/3));
		Pie(hDC,nCentreX-R/2,nCentreY-R/2,
			nCentreX+R/2,nCentreY+R/2,
			(int)(nCentreX+R/2*cos(fAngle+2*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+2*Pi/3)),
			(int)(nCentreX+R/2*cos(fAngle+Pi+2*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+Pi+2*Pi/3)));

		hBrush = CreateSolidBrush(RGB(0,255,255));		//画黄色的叶片.
		SelectObject(hDC,hBrush);
		nCentreX = (int)(R/2*cos(fAngle+4*Pi/3));
		nCentreY = (int)(R/2*sin(fAngle+4*Pi/3));
		Pie(hDC,nCentreX-R/2,nCentreY-R/2,
			nCentreX+R/2,nCentreY+R/2,
			(int)(nCentreX+R/2*cos(fAngle+4*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+4*Pi/3)),
			(int)(nCentreX+R/2*cos(fAngle+Pi+4*Pi/3)),(int)(nCentreY+R/2*sin(fAngle+Pi+4*Pi/3)));
		
		EndPaint(hWnd,&PtStr);		//释放环境指针。
		nNum++;						//当前序数加1.
		SetWindowLong(hWnd,4,nNum);	//将该窗口风车的转动次数存于窗口附加信息中

		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd,NULL,1);	//重绘窗口区域.
		break;
	case WM_DESTROY:	//关闭窗口.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return DefWindowProc (hWnd, iMessage, wParam, lParam) ;
}