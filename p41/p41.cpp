#include<windows.h>
#include<tchar.h>
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
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	HDC hDC;   			//定义指向设备上下文的句柄
	PAINTSTRUCT PtStr; 	//定义指向包含绘图信息的结构体变量
	HBRUSH hBrush;  		//定义指向画刷的句柄
	HPEN hPen;			//定义指向画笔的句柄
	static int dispMode = -1;
	LPCTSTR str;
	switch(iMessage)  //处理消息
	{
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:    							//处理绘图消息
		hDC=BeginPaint(hWnd,&PtStr);
		dispMode = (dispMode+1)%6;
		switch(dispMode)
		{
		case 0:
			str = _T("映射方式MM_TEXT：缺省的映射方式");
			SetMapMode(hDC,MM_TEXT);  		//设置映像模式
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 1:
			str = _T("映射方式MM_ISOTROPIC：窗口坐标为20×20，映射为视口尺寸为10×10，图形缩小1倍");
			SetMapMode(hDC,MM_ISOTROPIC);  		
			SetWindowExtEx(hDC,20,20,NULL);		//窗口矩形为20×20
			SetViewportExtEx(hDC, 10, 10, NULL);//映射为视口的矩形为10×10
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 2:
			str = _T("映射方式MM_ISOTROPIC：窗口坐标为10×10，映射为视口尺寸为20×20，图形放大1倍");
			SetMapMode(hDC,MM_ISOTROPIC);  		
			SetWindowExtEx(hDC,10,10,NULL);		//窗口矩形为10×10
			SetViewportExtEx(hDC, 20, 20, NULL);//映射为视口的矩形为20×20
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 3:
			str = _T("映射方式MM_ANISOTROPIC：窗口坐标为10×10，映射为视口尺寸为20×10，图形横向放大1倍，纵向不变");
			SetMapMode(hDC,MM_ISOTROPIC);  		//设置映像模式
			SetWindowExtEx(hDC,10,10,NULL);		//窗口矩形为10×10
			SetViewportExtEx(hDC, 20, 10, NULL);//映射为视口的矩形为20×10
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 4:
			str = _T("映射方式MM_ANISOTROPIC：窗口坐标为10×10，映射为视口尺寸为20×5，图形横向放大1倍，纵向缩小1倍");
			SetMapMode(hDC,MM_ANISOTROPIC);  		//设置映像模式
			SetWindowExtEx(hDC,10,10,NULL);		//窗口矩形为10×10
			SetViewportExtEx(hDC, 20, 5, NULL);//映射为视口的矩形为20×5
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		case 5:
			str = _T("映射方式MM_ISOTROPIC：窗口坐标为10×10，映射为视口尺寸为20×5，图形为了保持纵横比，系统会调整映射比例");
			SetMapMode(hDC,MM_ISOTROPIC);  		//设置映像模式
			SetWindowExtEx(hDC,10,10,NULL);		//窗口矩形为10×10
			SetViewportExtEx(hDC, 20, 5, NULL);//映射为视口的矩形为20×5
			TextOut(hDC, 0, 0, str, _tcslen(str));
			break;
		}
		hPen=(HPEN)GetStockObject(BLACK_PEN);//设置画笔为系统预定定义的黑色画笔
		hBrush=(HBRUSH)GetStockObject(DKGRAY_BRUSH); //采用系统预定义的深灰色画刷
		SelectObject(hDC,hBrush);  			//选择画刷
		SelectObject(hDC,hPen);    			//选择画笔
		RoundRect(hDC,50,120,100,200,15,15); //圆角矩形
		hBrush=(HBRUSH)GetStockObject(LTGRAY_BRUSH); //采用系统预定义的亮灰色画刷
		SelectObject(hDC,hBrush);  			//选择画刷
		Ellipse(hDC,150,50,200,150); 		//椭圆
		hBrush=(HBRUSH)GetStockObject(HOLLOW_BRUSH); //采用系统预定义的虚画刷
		SelectObject(hDC,hBrush);  			//选择画刷
		Pie(hDC,250,50,300,100,250,50,300,50);  	//饼形
		EndPaint(hWnd,&PtStr);  				//结束绘图
		return 0;
	case WM_DESTROY: 						//结束应用程序
		PostQuitMessage(0);
		return 0;
	default:									//其他消息处理程序
		return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
		break;
	}
	return 0;
}
 
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//定义窗口类
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("窗口示例");
	TCHAR *szTitle = _T("映射模式及填充示例图");
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
