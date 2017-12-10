#include<windows.h>
#include<tchar.h>
#include<math.h>
#define PI 3.1415926
BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HFONT CreateMyFont(LPWSTR fontName,int height,int lean);
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
	HFONT font;
	HPEN hPen;		//定义指向画笔的句柄
	LPWSTR title = L"登高 唐·杜甫",
		poem[8] = {L"风急天高猿啸哀", L"渚清沙白鸟飞回",
					L"无边落木萧萧下", L"不尽长江滚滚来", 
					L"万里悲秋常作客", L"百年多病独登台",
					L"艰难苦恨繁霜鬓", L"潦倒新停浊酒杯"};
	LPCWSTR outInfo;
	int r, r0, i, j=-1, fontSize, fontSize0, color;
	RECT clientDimension;
	POINT begin, end, org;
	double sita;

	switch(Message)  //处理消息
	{
	case WM_PAINT:    							//处理绘图消息
		hDC=BeginPaint(hWnd,&ps);
		hPen = CreatePen(PS_DASH, 1, RGB(127, 127, 127));
		SelectObject(hDC, hPen);
		GetClientRect(hWnd, &clientDimension);
		if( (clientDimension.right-clientDimension.left)<400 ||
			(clientDimension.bottom-clientDimension.top)<300 )
		{
			MessageBox(hWnd, _T("屏幕尺寸太小，无法绘图！"), _T("错误信息"),0);
			break;
		}
		r = (clientDimension.bottom-clientDimension.top)*8/10;
		org.x = (clientDimension.right-clientDimension.left)/2;
		org.y = (clientDimension.bottom-clientDimension.top)*9/10;
		Arc(hDC, org.x-r, org.y-r,org.x+r,org.y+r,
			org.x+(int)(r*sin(PI/3)),org.y-(int)(r*cos(PI/3)),
			org.x-(int)(r*sin(2*PI/3)),org.y+(int)(r*cos(2*PI/3)));
		for(sita=PI/6; sita<=PI*5/6; sita+=PI*2/27)
		{
			begin.x = org.x-(int)(r*cos(sita));
			begin.y = org.y-(int)(r*sin(sita));
			MoveToEx(hDC, begin.x,begin.y,NULL);
			end.x = org.x;
			end.y = org.y;
			LineTo(hDC,end.x,end.y);
		}
		r0 = r * 2 / 5;
		Arc(hDC, org.x-r0, org.y-r0,org.x+r0,org.y+r0,
			org.x+(int)(r0*sin(PI/3)),org.y-(int)(r0*cos(PI/3)),
			org.x-(int)(r0*sin(2*PI/3)),org.y+(int)(r0*cos(2*PI/3)));
		sita = PI/6 + PI*4/15/5;
		fontSize0 = fontSize = (r-r0)/7;
		r0 = r-20;
		for(i=0; i<7; i++)
		{
			outInfo = &title[i];
			fontSize -= 3;
			font = CreateMyFont(L"楷体_GB2312", fontSize-5,-(sita+PI/15)*1800/PI);
			SelectObject(hDC,font);
			begin.x = org.x + (int)(r0*cos(sita));
			begin.y = org.y - (int)(r0*sin(sita));
			TextOutW(hDC, begin.x, begin.y, outInfo,1);
			r0 -= fontSize;
			DeleteObject(font);
		}
		for(sita=PI/6+PI*4/27-PI/40; sita<PI*5/6; sita += PI*2/27)
		{
			fontSize = fontSize0;
			r0 = r-20;
			j++;
			color = 0;
			for(i=0; i<7; i++)
			{
				color += 255/7;
				SetTextColor(hDC, RGB(255-color,0,color));
				LPCWSTR outInfo = &poem[j][i];
				fontSize -= 3;
				font = CreateMyFont(L"华文行楷",fontSize, (int)(((sita-PI/2)*1800/PI))%3600);
				SelectObject(hDC,font);
				begin.x = org.x + (int)(r0*cos(sita));
				begin.y = org.y - (int)(r0*sin(sita));
				TextOutW(hDC, begin.x,begin.y,outInfo,1);
				r0 -= fontSize;
				DeleteObject(font);
				Sleep(10);
			}
		}
		EndPaint(hWnd,&ps);  				//结束绘图
		break;
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
 
HFONT CreateMyFont(LPWSTR fontName, int height, int lean)
{
	return CreateFontW(
						height,				//字体的高度
						0,				//由系统根据高宽比选取字体最佳宽度值
						lean,				//文本的倾斜度为0，表示水平
						0,				//字体的倾斜度为0
						FW_HEAVY,		//字体的粗度，FW_HEAVY为最粗
						0,				//非斜体字
						0,				//无下划线
						0,				//无删除线
						GB2312_CHARSET,	//表示所用的字符集为ANSI_CHARSET
						OUT_DEFAULT_PRECIS,	//输出精度为缺省精度
						CLIP_DEFAULT_PRECIS,	//剪裁精度为缺省精度
						DEFAULT_QUALITY,		//输出质量为缺省值
						DEFAULT_PITCH|FF_DONTCARE,//字间距和字体系列使用缺省值
						fontName				//字体名称
						);

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
