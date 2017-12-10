#include<windows.h>
#include<tchar.h>
#include<math.h>
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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
	HBRUSH hBrush;  		//定义指向画刷的句柄
	HPEN hPen;			//定义指向画笔的句柄
	RECT clientRect,rc;
	static RECT oldClientRect = {0,0,0,0};
	float sita = 0;
	int a[4] = {75,50,60,90}, maxValue, i, xOrg, yOrg,
		deltaX,deltaY,xBegin,yBegin,xEnd,yEnd, s=0;
								/* /////	 \\\\\		 +++++		 xxxxx */
	int hatchBrushStyle[4] = {HS_BDIAGONAL, HS_FDIAGONAL,HS_CROSS, HS_DIAGCROSS};
								//red			green		blue		Violet
	COLORREF colorIndex[4] = {RGB(255,0,0), RGB(0,255,0), RGB(0,0,255), RGB(255,0,255)};

	switch(Message)  //处理消息
	{
	case WM_PAINT:    							//处理绘图消息
		maxValue = a[0];
		for(i=0; i<4; i++)
		{
			s+=a[i];
			if(a[i]>maxValue)
				maxValue = a[i];
		}
		hDC=BeginPaint(hWnd,&ps);
		GetClientRect(hWnd, &clientRect);
		if((clientRect.right-clientRect.left)<300 ||
			(clientRect.bottom-clientRect.top)<300)
		{
			MessageBox(hWnd, _T("屏幕尺寸太小，无法绘图！"), _T("错误信息"),0);
			EndPaint(hWnd, &ps);
			break;
		}
		hPen=(HPEN)GetStockObject(BLACK_PEN);//设置画笔为系统预定定义的黑色画笔
		SelectObject(hDC,hPen);    			//选择画笔
		Rectangle(hDC, clientRect.left + 10, clientRect.top + 10,
			clientRect.right - 10, clientRect.bottom -10);
		MoveToEx(hDC, (clientRect.left+clientRect.right)/2, clientRect.top + 10, NULL);
		LineTo(hDC,(clientRect.left+clientRect.right)/2, clientRect.bottom - 10);

		xOrg = clientRect.left + 60;
		yOrg = clientRect.bottom -60;
		xEnd = (clientRect.left+clientRect.right)/2 - 50;
		yEnd = yOrg;
		deltaX = (xEnd - xOrg - 100)/4;
		MoveToEx(hDC, xOrg, yOrg, NULL);
		LineTo(hDC, xEnd, yEnd);		//画横轴
		xEnd = xOrg;
		yEnd = clientRect.top + 60;
		MoveToEx(hDC, xOrg, yOrg, NULL);
		LineTo(hDC, xEnd, yEnd);		//画纵轴
		deltaY = (yOrg - yEnd - 100)/maxValue;

		hPen = CreatePen(PS_SOLID,1,RGB(127,127,127));
		SelectObject(hDC, hPen);
		for(i=0; i<4; i++)	//画4个柱形图
		{
			hBrush = CreateHatchBrush(hatchBrushStyle[i], colorIndex[i]);
			SelectObject(hDC, hBrush);
			xBegin = xOrg + deltaX * i;
			yBegin = yOrg;
			xEnd = xBegin + deltaX;
			yEnd = yOrg - deltaY * a[i];
			Rectangle(hDC, xBegin, yBegin, xEnd, yEnd);
		}
		
		xOrg = clientRect.left + (clientRect.right-clientRect.left)*3/4 + 10;
		yOrg = clientRect.top + (clientRect.bottom - clientRect.top)/2 + 10;
		deltaX = deltaY = min((clientRect.right-clientRect.left)/4,
							(clientRect.bottom-clientRect.top)/2)-50;
		xBegin = xOrg + 10;
		yBegin = yOrg;
		for(i=0; i<4; i++)
		{
			hBrush = CreateSolidBrush(colorIndex[i]);
			SelectObject(hDC, hBrush);
			sita = sita-2*3.14159*a[i]/s;
			xEnd = xOrg + 10 * cos(sita);
			yEnd = yOrg + 10 * sin(sita);
			Pie(hDC, xOrg-deltaX,yOrg-deltaY, xOrg+deltaX,yOrg+deltaY,xBegin,yBegin,xEnd,yEnd);
			xBegin = xEnd;
			yBegin = yEnd;
		}
		DeleteObject(hPen);
		DeleteObject(hBrush);
		EndPaint(hWnd,&ps);  				//结束绘图
		return 0;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY: 						//结束应用程序
		PostQuitMessage(0);
		return 0;
	default:									//其他消息处理程序
		return(DefWindowProc(hWnd, Message,wParam,lParam)) ;
		break;
	}
	return 0;
}
 
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//定义窗口类
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("窗口示例");
	TCHAR *szTitle = _T("柱形图及饼图显示数据统计");
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
	if( !RegisterClassEx( &wcex))		//如果注册失败则发出警告声音
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
