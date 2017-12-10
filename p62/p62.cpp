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
//������
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	hinst = hInstance;
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
	WORD x,y;         		//�����ʾ����ı���
	HCURSOR hCursor;  		//�����ʾ���ı���
	char s[80];
	switch(iMessage)  		//��Ϣ����
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
	case WM_MOUSEMOVE:   	//��������ƶ���Ϣ
		x=LOWORD(lParam); //ȡ���������λ���ڹ������е�����ֵ
		y=HIWORD(lParam);
	//�������Ͻ�Ϊ(50,50)�����½�Ϊ(400,300)ȷ���ľ���������ʱ���ñ�������״
		if(x>=50&&x<=400&&y>=50&&y<=300)  
		{
			if(x>=50&&x<=100&&y>=50&&y<=100)
			{
				hCursor=LoadCursor(NULL,IDC_CROSS); //����һ��"ʮ"�������
				SetCursor(hCursor);//���õ�ǰ���Ϊ�Ͼ��ж����"ʮ"�������
			}
			if(x>=100&&x<=150&&y>=50&&y<=100)
			{
				hCursor=LoadCursor(NULL,IDC_SIZE); //����һ��˫��ͷ�����
				SetCursor(hCursor);	//���õ�ǰ���Ϊ�Ͼ��ж����˫��ͷ�����
			}
			if(x>=150&&x<=200&&y>=50&&y<=100)
			{
				hCursor=LoadCursor(NULL,IDC_SIZE); //����һ��˫��ͷ�����
				SetCursor(hCursor);	//���õ�ǰ���Ϊ�Ͼ��ж����˫��ͷ�����
			}
			if(x>=50&&x<=100&&y>=100&&y<=150)
			{
				//����һ�����ڸñ䴰��Խ��ߴ�С��˫��ͷ�����
				hCursor=LoadCursor(NULL,IDC_SIZENESW);
				SetCursor(hCursor);//���õ�ǰ���Ϊ�Ͼ��ж�������
			}
			if(x>=100&&x<=250&&y>=100&&y<=150)
			{
				//�������Ϊ�ı����´�С��˫��ͷ�����
				hCursor=LoadCursor(NULL,IDC_SIZENS); 
				SetCursor(hCursor);
			}
			if(x>=250&&x<=400&&y>=100&&y<=150)
			{
				//����һ�����ڸñ䴰��Խ��ߴ�С��˫��ͷ�����
				hCursor=LoadCursor(NULL,IDC_SIZENWSE); 
				SetCursor(hCursor);
			}
			if(x>=50&&x<=100&&y>=150&&y<=300)
			{
				//����һ�����ڸñ䴰�����ҷ����ϴ�С��˫��ͷ�����
				hCursor=LoadCursor(NULL,IDC_SIZEWE);
				SetCursor(hCursor);
			}
			if(x>=100&&x<=250&&y>=150&&y<=300)
			{
				//����һ���������ϵļ�ͷ�����
				hCursor=LoadCursor(NULL,IDC_UPARROW);
				SetCursor(hCursor);
			}
			if(x>=250&&x<=400&&y>=150&&y<=300)
			{	//����һ�����ڱ�ʾϵͳæ�����
				hCursor=LoadCursor(NULL,IDC_WAIT);
				SetCursor(hCursor);
			}
		}
		else
		{
			hCursor=LoadCursor(hinst,(LPCTSTR)IDC_CURSOR1);//IDC_ARROW);  //�����������ó���ͨ�ļ�ͷ�����
			SetCursor(hCursor);
		}
		return 0;
	case WM_DESTROY: //�������Ӧ�ó�����Ϣ
		PostQuitMessage(0);//����Ӧ�ó���
		return 0;
	default://������Ϣ�������
		return(DefWindowProc(hWnd,iMessage,wParam,lParam)) ;
	}
}

BOOL InitWindowsClass(HINSTANCE hInstance) //��ʼ��������
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

BOOL InitWindows(HINSTANCE hInstance,int nCmdShow) //��ʼ������
{
	HWND hWnd;
	hWnd=CreateWindow("WinMouse",  //���ɴ���
					"��꼰�����״����ʾ��",
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
