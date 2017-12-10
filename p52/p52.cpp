#include <windows.h>
#include <tchar.h>
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
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,UINT wParam,LONG lParam)
{
	HDC hdc;
	HFONT hF_black,hF_big;	//定义两种字体句柄
	PAINTSTRUCT ps;
	TEXTMETRIC tm;			//定义一个TEXTMETRIC结构，用以记录字体信息
	LPCWSTR lpsz_1 = L"这是一行红色的、字体为SYSTEM_FONT的文字，红色代表未来。";
	LPCWSTR lpsz_2 = L"现在显示的是自定义字体，颜色为绿色，绿色代表生机勃勃。";
	LPCWSTR lpsz_3 = L"现在展现在您面前的是蓝色的粗体字，蓝色代表广阔的海洋和天空。";
	LPCWSTR lpsz_4 = L"当前字体为大号、斜体并带有下划线的文字。";
	LPCWSTR lpsz_5 = L"现在您掌握了字体的操作了吗?";
	LPCWSTR lpsz_6 = L"祝您成功!";
	LPCWSTR lpsz_7 = L"VC2008是一门计算机专业的重要课程!";

	int X=0,Y=0;
	static RECT rect = {0,300,0,350};
	SIZE size;					//定义一个SIZE类型的结构

	switch(message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 9999, 50, NULL);
		break;
	case WM_TIMER:
		if(wParam==9999)
			InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		rect.right += 2;
		hdc=BeginPaint(hWnd,&ps);
		SetTextColor(hdc,RGB(255,0,0));	//设置文本颜色为红色
		GetTextMetrics(hdc,&tm);	//获取缺省字体，写入tm结构中
		TextOutW(hdc,X,Y,lpsz_1, wcslen(lpsz_1));	//使用当前字体输出文本
		Y=Y+tm.tmHeight+100*tm.tmExternalLeading;//计算换行时下一行文本的输出坐标	
								
		//创建自定义字体
		hF_black=CreateFont(
				20,				//字体的高度
				0,				//由系统根据高宽比选取字体最佳宽度值
				0,				//文本的倾斜度为0，表示水平
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
				"粗体字"				//字体名称
			);

		SetTextColor(hdc,RGB(0,255,0));	//设置文本颜色为绿色
		SelectObject(hdc,hF_black);		//将自定义字体选入设备环境
		GetTextMetrics(hdc,&tm);		//获取字体的信息，并写入tm结构中
		TextOutW(hdc,X,Y,lpsz_2,wcslen(lpsz_2));//使用当前字体输出文本
		//换行继续输出文本，计算新行的起始Y坐标位置
		Y=Y+tm.tmHeight+10*tm.tmExternalLeading;	
		GetTextExtentPoint32W(hdc,lpsz_2,wcslen(lpsz_2),&size);
													//获取字符串/的宽度
		SetTextColor(hdc,RGB(0,0,255));	//设置文本颜色为蓝色
		TextOutW(hdc,X,Y,lpsz_3,wcslen(lpsz_3));//用当前字体输出文本
		//X=0;					//计算下一行文本的输出起始坐标
		Y=Y+tm.tmHeight+20*tm.tmExternalLeading; 
		hF_big=CreateFont(		//引入新字体
			30,					//字体高度
			0,
			0,
			0,
			FW_NORMAL,
			1,			//定义斜体
			1,			//定义输出时带下划线
			0,
			GB2312_CHARSET,	//所使用的字符集
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"大号字"
		);

		SelectObject(hdc,hF_big);	//将第二种自定义字体选入设备环境
		SetTextColor(hdc,RGB(155,155,155));	//设置文本颜色为灰色
		Y=Y+tm.tmHeight+5*tm.tmExternalLeading;	
 		TextOutW(hdc,X,Y,lpsz_4,wcslen(lpsz_4));//以当前字体输出文本
		SetTextColor(hdc,RGB(255,0,0));	//设置文本颜色为红色

		Y=Y+tm.tmHeight+10*tm.tmExternalLeading;	
		TextOutW(hdc,X,Y,lpsz_5,wcslen(lpsz_5)); 	//输出文本
		//在该行继续输出文本
		GetTextExtentPoint32W(hdc,lpsz_5,wcslen(lpsz_5),&size);//获取字符串的宽度
		X=X+size.cx;							//获取起始坐标
		TextOutW(hdc,X,Y,lpsz_6,wcslen(lpsz_6)); 	//输出文本

		hF_big=CreateFont(		//引入新字体
			48,					//字体高度
			0,
			0,
			0,
			FW_NORMAL,
			0,			//定义斜体
			0,			//定义输出时带下划线
			0,
			GB2312_CHARSET,	//所使用的字符集
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"楷体_GB2312"
		);
		SelectObject(hdc, hF_big);
		SetTextColor(hdc, RGB(0,0,0));
		SetBkColor(hdc, RGB(100,150,100));
		TextOutW(hdc, 0, 300, lpsz_7, wcslen(lpsz_7));
		SetTextColor(hdc, RGB(0,255,0));
		SetBkColor(hdc, RGB(150,50,50));
		DrawTextW(hdc, lpsz_7, wcslen(lpsz_7), &rect, DT_LEFT);
		GetTextExtentPoint32W(hdc,lpsz_7,wcslen(lpsz_7),&size);//获取字符串的宽度
		if(rect.right>=size.cx)
			rect.right=0;
		EndPaint(hWnd,&ps);
		DeleteObject(hF_black);
		DeleteObject(hF_big);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return  DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow) 			//定义窗口类
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR *szWindowClass = _T("窗口示例");
	TCHAR *szTitle = _T("文本输出示例");
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