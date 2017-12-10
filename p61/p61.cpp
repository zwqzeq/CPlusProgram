#include<windows.h>
#include<stdlib.h>
#include<string.h>
void WINAPI CaretPos(HWND hWnd,int nArrayPos,char *cCharBuf,int *xCaret,int *yCaret,int nCharWidth);
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
HWND hWndMain;

//主函数
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
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
#define BufSize 30					//设置存放字符的缓冲区大小		
	static char cCharBuf[BufSize];	//设置静态字符数组，存放输入的字符，字符个数不能超出缓冲区大小
	static int nNumChar=0;		//现有字符个数
	static int nArrayPos=0;		//字符的位置
	static int nLnHeight;
	static int nCharWidth;
	static int xCaret,yCaret;
	int x;
	HDC hDC;
		TEXTMETRIC tm;
	PAINTSTRUCT PtStr; //定义指向包含绘图信息的结构体变量
		switch(iMessage)  //处理消息
		{
			case WM_CHAR:				//遇到非系统字符所作的处理
			{
				if(wParam==VK_BACK)  	//处理"遇到回退键的消息"
			 	{
					if(nArrayPos==0) //如果已经在一行文字的开始处，则提示用户"不能回退"
						MessageBox(hWnd,"当前位置是文本的起始位置，不能回退",NULL,MB_OK);
					else
					{
						nArrayPos=nArrayPos-1; //每按一次回退键就回退一个字符的位置
						for(x=nArrayPos;x<nNumChar-1;x++)
							cCharBuf[x]=cCharBuf[x+1];
						CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						nNumChar=nNumChar-1;	//对现有字符总数进行计数
						InvalidateRect(hWnd,NULL,TRUE);	//刷新用户区，并向应用程序发送WM_PAINT消息
					}
					break;
				}
				if(wParam<=VK_ESCAPE) //处理按下Escape键消息
				{
					MessageBox(hWnd,"您现在不能按ESC键，请继续其它操作",NULL,MB_OK);
					break;
				}
				if(nNumChar>=BufSize) //如果写入的字符数超过缓冲区大小，则报警
				{
					MessageBox(hWnd,"缓冲区已满，不能再输入字符了\n若需要删除字符，请用BackSpace键",NULL,MB_OK);
					break;
				}
				for(x=nNumChar;x>nArrayPos;x=x-1)
					cCharBuf[x]=cCharBuf[x-1];
				cCharBuf[nArrayPos]=(unsigned char)wParam;
				nArrayPos=nArrayPos+1;
				nNumChar=nNumChar+1;
				CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
				InvalidateRect(hWnd,NULL,TRUE);
			}
			break;

		case WM_CREATE: //处理窗口创建消息
			{
				hDC=GetDC(hWnd);
				GetTextMetrics(hDC,&tm); //获取字体信息
				nLnHeight=tm.tmHeight+tm.tmExternalLeading;
				nCharWidth=tm.tmAveCharWidth;
				yCaret=nLnHeight;
				ReleaseDC(hWnd,hDC);
			}
			break;
		case WM_SETFOCUS: //处理活动焦点消息
			{
				CreateCaret(hWnd,0,0,nLnHeight);
				CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
				ShowCaret(hWnd); //在活动焦点的窗口中显示插字符
			}
			break;
		case WM_KILLFOCUS: //处理失去焦点消息
			DestroyCaret();
			break;
		case WM_KEYDOWN: //处理按下键消息
			{
				switch(wParam)
				{
					case VK_END: //处理按下键为End时的消息
						nArrayPos=nNumChar;	//输入位置从本行的末尾开始
						CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						break;
					case VK_HOME:	//处理按下键为Home时的消息
						nArrayPos=0;	//输入位置为本行的起始位置
						CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						break;
					case VK_DELETE://处理按下键为Delete时的消息
						if(nArrayPos==nNumChar)  //输入位置处于本行的末尾
							MessageBox(hWnd,"光标位置已经到行尾，没有字符可供删除",NULL,MB_OK);
						else
						{
							for(x=nArrayPos;x<nNumChar-1;x=x+1)
								cCharBuf[x]=cCharBuf[x+1];	//每删除一个字符，缓冲区中总字符数减1
							nNumChar=nNumChar-1;
							InvalidateRect(hWnd,NULL,TRUE); //用户区刷新
						}
						break;
					case VK_LEFT: //处理按下左方向键时的消息
						if(nArrayPos>0)
						{
							nArrayPos=nArrayPos-1;  //当前输入位置往前移一个位置，再输入字符时，等于插入字符
							CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						}
						else	//已经移到起始输入位置，不能再往前了
							MessageBox(hWnd,"您已经移动到起始位置，不能再往左移动了",NULL,MB_OK);
						break;
					case VK_RIGHT://处理按下右方向键时的消息
						if(nArrayPos<nNumChar)	//如果当前位置没有到缓冲区的最后位置，还能向右移动	
						{
							nArrayPos=nArrayPos+1;
							CaretPos(hWnd,nArrayPos,cCharBuf,&xCaret,&yCaret,nCharWidth);
						}
						else
							MessageBox(hWnd,"已经到缓冲区的末尾,不能再向右移动了",NULL,MB_OK);
						break;
				}
			}
			break;
		case WM_PAINT: //处理重画消息
			{
				hDC=BeginPaint(hWnd,&PtStr);
				TextOut(hDC,nCharWidth,nLnHeight,cCharBuf,nNumChar); //输出缓冲区中的文本
				EndPaint(hWnd,&PtStr);
			}
			break;
	case WM_DESTROY: //处理结束应用程序消息
			PostQuitMessage(0);//结束应用程序
			break;
	default://其他消息处理程序
			return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
		}
		return 0;
}

void WINAPI CaretPos(HWND hWnd,int nArrayPos,char *cCharBuf,int *xCaret,int *yCaret,int nCharWidth)					//处理插字符位置的函数
{
	DWORD dWord; 
	SIZE size;
	HDC hDC;								//定义设备描述表句柄
	hDC=GetDC(hWnd);//取得当前设备描述表句柄
	GetTextExtentPoint32(hDC,cCharBuf,nArrayPos,&size);//获取光标位置
	dWord=size.cx;
	ReleaseDC(hWnd,hDC); 
	*xCaret=LOWORD(dWord)+nCharWidth;
	SetCaretPos(*xCaret,*yCaret);		//设置插字符位置坐标
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
		WndClass.lpszClassName="WinKeyboard";
		WndClass.lpszMenuName=NULL;
		WndClass.style=CS_HREDRAW|CS_VREDRAW;
		return RegisterClass(&WndClass);
}

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow)//初始化窗口
{	
		HWND hWnd;
		hWnd=CreateWindow("WinKeyboard",  		//生成窗口
						"键盘操作例程",
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
	ShowWindow(hWnd,nCmdShow);	//显示窗口
	UpdateWindow(hWnd);			//绘制用户区
		return TRUE;
}
