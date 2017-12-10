#include<windows.h>
#include<stdlib.h>
#include<string.h>
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);
BOOL InitWindows(HINSTANCE hInstance,int nCmdShow);
HWND hWndMain;

//������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG Message;
	if(!InitWindowsClass(hInstance))
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))
		return FALSE;
	while(GetMessage(&Message,0,0,0))//��Ϣѭ��
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		return Message.wParam;
}

//��Ϣ������
long WINAPI WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
		static long nXChar,nCaps,nYChar;
	HDC hDC;   //����ָ���豸�����ĵľ��	
	HFONT f;
	short x;
    TEXTMETRIC tm;
		short LnCount=8;
		PAINTSTRUCT PtStr; //����ָ�������ͼ��Ϣ�Ľṹ�����
		static char *textbuf[]=
			{
			"OEM_FIXED_FONT:OEM�ַ����Ĺ�������",
			"ANSI_FIXED_FONT:����windows��ANSI���ַ����ĵȿ�����",
			"ANSI_VAR_FONT:����windows��ANSI���ַ����Ĳ��ȿ�����",
			"SYSTEM_FONT: Ĭ������,��Ļϵͳ���塣�������ڲ˵����Ի���ȵȵ�Ĭ�ϲ��ȿ�����",
			"DEVICE_DEFAULT_FONT:�豸ʹ�õ�Ĭ�����壨NT��",
			"DEFAULT_PALETTE:Ĭ�ϵ�ɫ��",
			"SYSTEM_FIXED_FONT:��Ļϵͳ���塣�������ڲ˵����Ի���ȵȵ�Ĭ�ϵȿ����壨��windows 3.0֮ǰʹ�ã�",
			"DEFAULT_GUI_FONT:�û������Ĭ�����壬�����˵��ͶԻ������壨Windows 95��"
		};
	switch(iMessage)  //������Ϣ
		{
			case WM_CREATE:	//�����ڴ�����Ϣ
				hDC=GetDC(hWnd) ;   //��ȡ��ǰ�豸����
				GetTextMetrics(hDC,&tm); //��ȡ������Ϣ
				nXChar=tm.tmAveCharWidth;  //��ȡ�ַ����
				nYChar=tm.tmHeight+tm.tmExternalLeading;
				nCaps=(tm.tmPitchAndFamily&1?3:2)*nXChar/2;
				ReleaseDC(hWnd,hDC);  //�ͷŵ�ǰ�豸���
				return 0;
			case WM_PAINT: //�����ػ���Ϣ
				hDC=BeginPaint(hWnd,&PtStr); //��ʼ�滭
				for(x=0;x<LnCount;x=x+1)  
				{    //����ı�
					f = (HFONT)GetStockObject(10 + x);
					SelectObject(hDC,f);
					TextOut(hDC,nXChar,50+30*x,textbuf[x],lstrlen(textbuf[x])); 
				}
				EndPaint(hWnd,&PtStr);
				return 0;
			case WM_DESTROY: //����Ӧ�ó���
				PostQuitMessage(0);
				return 0;
			default://������Ϣ�������
				return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
		}
}

BOOL InitWindowsClass(HINSTANCE hInstance)//��ʼ��������
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

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow) //��ʼ������
{
	HWND hWnd;
		hWnd=CreateWindow("WinText",  //���ɴ���
						"�ı���ʾʾ������",
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
		ShowWindow(hWnd,nCmdShow);//��ʾ����
	 UpdateWindow(hWnd);
		return TRUE;
}
